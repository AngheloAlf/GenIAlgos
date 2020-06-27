#include "picCompression.h"

#include <stdbool.h>
#include <string.h>


typedef struct{
    size_t size;
    uint8_t *arr;
} Array8_t;

typedef struct{
    size_t size;
    uint8_t *arr;
    size_t width, height;
} Matrix8_t;

typedef struct{
    Array8_t bytes_arr;
    uint16_t byte_index;
    uint8_t bit_index;
    uint8_t actual_byte;
} BitIterator_t;


static const uint16_t rle_table[] = {
    0x0001, 0x0003, 0x0007, 0x000f,
    0x001f, 0x003f, 0x007f, 0x00ff,
    0x01ff, 0x03ff, 0x07ff, 0x0fff,
    0x1fff, 0x3fff, 0x7fff, 0xffff,
};
static const uint8_t table_0x2867[] = {
    0x00, 0x08, 0x04, 0x0C, 
    0x02, 0x0A, 0x06, 0x0E, 
    0x01, 0x09, 0x05, 0x0D, 
    0x03, 0x0B, 0x07, 0x0F
};
static const uint8_t Met1Table1UnMirr[] = {
    0x01, 0x32, 0x76, 0x45, 
    0xFE, 0xCD, 0x89, 0xBA
};
static const uint8_t Met1Table1Mirr[]   = {
    0x08, 0xC4, 0xE6, 0x2A, 
    0xF7, 0x3B, 0x19, 0xD5
};


static uint8_t RLC(uint8_t number){
    return ((number & 0b01111111) << 1) | ((number & 0b10000000) >> 7);
}
static uint8_t RRC(uint8_t number){
    return ((number & 0b11111110) >> 1) | ((number & 0b00000001) << 7);
}
static uint8_t SWAP(uint8_t number){
    return ((number & 0x0F) << 4) | ((number & 0xF0) >> 4);
}
static uint8_t BIT(uint8_t number, uint8_t bit_i){
    return (number >> bit_i) & 0x01;
}

uint8_t get_bit_group(uint8_t bit_group_id, uint8_t a){
    switch(bit_group_id){
    case 3:
        return RRC(RRC(a));
    case 2:
        return SWAP(a);
    case 1:
        return a << 2;
    default:
        return a;
    }
}

uint8_t get_next_byte(BitIterator_t *bit_iterator){
    uint8_t byte = bit_iterator->bytes_arr.arr[bit_iterator->byte_index];
    bit_iterator->byte_index += 1;
    return byte;
}
uint8_t get_next_bit(BitIterator_t *bit_iterator){
    if(bit_iterator->bit_index == 0){
        bit_iterator->actual_byte = get_next_byte(bit_iterator);
        bit_iterator->bit_index = 8;
    }
    bit_iterator->bit_index -= 1;
    bit_iterator->actual_byte = RLC(bit_iterator->actual_byte);
    return bit_iterator->actual_byte & 0b0001;
}

uint16_t rle_mode_loop(BitIterator_t *bit_iterator){
    uint8_t i;
    for(i = 0; get_next_bit(bit_iterator) != 0; ++i);
    uint16_t hl = rle_table[i];
    ++i;
    uint16_t de;
    for(de = 0; i != 0; --i){
        de <<= 1;
        de |= get_next_bit(bit_iterator);
    }
    return de + hl;
}

uint16_t process_bit_group(Matrix8_t *dst_buffer, uint16_t buffer_index, BitIterator_t *bit_iterator, uint16_t de, uint8_t bit_group){
    uint8_t actual_row_index = 0;
    if(de > 0){
        buffer_index += de;
        actual_row_index += de;
        de = actual_row_index >= dst_buffer->height ? actual_row_index - dst_buffer->height : 0;
    }
    while(actual_row_index < dst_buffer->height){
        uint8_t c = get_next_bit(bit_iterator) << 1;    // ; if it's 00-group
        c |= get_next_bit(bit_iterator);                // ; do RLE
        if(c == 0){
            de = rle_mode_loop(bit_iterator);
            buffer_index += de;
            actual_row_index += de;
            if(actual_row_index >= dst_buffer->height){
                return actual_row_index - dst_buffer->height;
            }
            de = 0;
            continue;
        }
        dst_buffer->arr[buffer_index] |= get_bit_group(bit_group, c);
        buffer_index += 1;
        actual_row_index += 1;
    }
    return de;
}

void extract_to_buffer(Matrix8_t *dst_buffer, BitIterator_t *bit_iterator){
    memset(dst_buffer->arr, 0, dst_buffer->size); // clean_buffer

    uint16_t de = 0;
    if(get_next_bit(bit_iterator) == 0){
        de = rle_mode_loop(bit_iterator);
    }

    uint16_t buffer_index = 0;
    for(uint8_t row_subindex = 0; row_subindex < dst_buffer->width; ++row_subindex){
        de = process_bit_group(dst_buffer, buffer_index, bit_iterator, de, 0b11);
        de = process_bit_group(dst_buffer, buffer_index, bit_iterator, de, 0b10);
        de = process_bit_group(dst_buffer, buffer_index, bit_iterator, de, 0b01);
        de = process_bit_group(dst_buffer, buffer_index, bit_iterator, de, 0b00);

        buffer_index += dst_buffer->height;
    }
}



uint8_t met_1_get_meta_code(const uint8_t metaCode1Table[8], uint8_t a, uint8_t e, bool mirror){
    bool high_nibble = (a & 1) == 0;
    a /= 2;
    uint8_t metacode = metaCode1Table[a];
    if((mirror && BIT(e, 3)) || BIT(e, 0)){
        metacode = metaCode1Table[(4+a)%8];
    }
    return (high_nibble ? SWAP(metacode) : metacode) & 0x0f;
}

void interp_method_1(Matrix8_t *buffer, bool mirror){
    const uint8_t *metaCode1Table = mirror ? Met1Table1Mirr : Met1Table1UnMirr;
    uint16_t buffer_offset = 0;
    for(uint8_t actual_row_index = 0; actual_row_index < buffer->height; ++actual_row_index){
        uint16_t buffer_index = buffer_offset;
        uint8_t e = 0;
        for(uint8_t row_subindex = 0; row_subindex < buffer->width; ++row_subindex){
            e = met_1_get_meta_code(metaCode1Table, SWAP(buffer->arr[buffer_index]) & 0x0f, e, mirror);
            e = SWAP(e) | met_1_get_meta_code(metaCode1Table, buffer->arr[buffer_index] & 0x0f, e, mirror);
            buffer->arr[buffer_index] = e;
            buffer_index += buffer->height;
        }
        buffer_offset += 1;
    }
}

void interp_2(Matrix8_t *buffer_1, Matrix8_t *buffer_2, bool mirror, uint8_t interpret_mode){
    if(interpret_mode == 2){
        interp_method_1(buffer_2, false);
    }
    interp_method_1(buffer_1, mirror);

    uint16_t buffer_index = 0;
    for(uint8_t row_subindex = 0; row_subindex < buffer_2->width; ++row_subindex){
        for(uint8_t actual_row_index = 0; actual_row_index < buffer_2->height; ++actual_row_index){
            if(mirror){
                uint8_t c = SWAP(table_0x2867[SWAP(buffer_2->arr[buffer_index]) & 0x0F]);
                buffer_2->arr[buffer_index] = c | table_0x2867[buffer_1->arr[buffer_index] & 0x0F];
            }
            buffer_2->arr[buffer_index] ^= buffer_1->arr[buffer_index];
            buffer_index += 1;
        }
    }
}

void interpret(Matrix8_t *buffer_1, Matrix8_t *buffer_2, bool mirror, uint8_t interpret_mode, bool invert_buffers){
    if(interpret_mode == 0){
        interp_method_1(buffer_1, mirror);
        interp_method_1(buffer_2, mirror);
        return;
    }

    if(invert_buffers){
        interp_2(buffer_2, buffer_1, mirror, interpret_mode);
        return;
    }
    interp_2(buffer_1, buffer_2, mirror, interpret_mode);
}


void decompress_rutine(Matrix8_t *buffer_1, Matrix8_t *buffer_2, BitIterator_t *bit_iterator, bool mirror){
    bool use_second_buffer = get_next_bit(bit_iterator);
    extract_to_buffer(use_second_buffer ? buffer_2 : buffer_1, bit_iterator);

    use_second_buffer = !use_second_buffer;
    uint8_t interpret_mode = get_next_bit(bit_iterator);
    if(interpret_mode != 0){
        interpret_mode = get_next_bit(bit_iterator) + 1;
    }
    extract_to_buffer(use_second_buffer ? buffer_2 : buffer_1, bit_iterator);

    interpret(buffer_1, buffer_2, mirror, interpret_mode, !use_second_buffer);
}

void decompressPicture(size_t dst_size, uint8_t *dst_buffer0, uint8_t *dst_buffer1, size_t compressed_size, uint8_t *compressed_arr){
    uint8_t dimensions = compressed_arr[0];
    uint8_t heightPixels = 8*(dimensions & 0x0F);
    uint8_t widthPixels = SWAP(dimensions) & 0x0F;

    Matrix8_t buff0 = {
        .size = dst_size,
        .arr = dst_buffer0,
        .width = widthPixels,
        .height = heightPixels
    };
    Matrix8_t buff1 = {
        .size = dst_size,
        .arr = dst_buffer1,
        .width = widthPixels,
        .height = heightPixels
    };
    BitIterator_t compressed = {
        .bytes_arr = {
            .size = compressed_size-1,
            .arr = &compressed_arr[1]
        },
        .byte_index = 0,
        .bit_index = 0,
        .actual_byte = 0
    };

    decompress_rutine(&buff0, &buff1, &compressed, false);
}
