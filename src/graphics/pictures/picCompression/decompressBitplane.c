#include "picCompression.h"

#include <string.h>

static uint8_t RLC(uint8_t number){
    return ((number & 0b01111111) << 1) | ((number & 0b10000000) >> 7);
}

static uint8_t get_next_byte(BitIterator_t *bit_iterator){
    uint8_t byte = bit_iterator->bytes_arr[bit_iterator->byte_index];
    bit_iterator->byte_index += 1;
    return byte;
}
static uint8_t get_next_bit(BitIterator_t *bit_iterator){
    if(bit_iterator->bit_index == 0){
        bit_iterator->actual_byte = get_next_byte(bit_iterator);
        bit_iterator->bit_index = 8;
    }
    bit_iterator->bit_index -= 1;
    bit_iterator->actual_byte = RLC(bit_iterator->actual_byte);
    return bit_iterator->actual_byte & 0b0001;
}



uint8_t readBitPair(BitIterator_t *bit_iterator){
    uint8_t pair = get_next_bit(bit_iterator) << 1;
    return pair | get_next_bit(bit_iterator);
}

uint16_t readRlePacket(BitIterator_t *bit_iterator){
    uint16_t l = 0;
    size_t i = 1;
    while(get_next_bit(bit_iterator)){
        l |= 1;
        l <<= 1;
        ++i;
    }
    uint16_t v = 0;
    while(i--){
        v <<= 1;
        v |= get_next_bit(bit_iterator);
    }
    return l + v + 1;
}

uint8_t get_bit_group(uint8_t bit_group_id, uint8_t pair){
    return pair << (2*bit_group_id);
}

uint16_t skip_n_zeros(uint16_t *n, uint16_t *row_index, uint16_t height){
    uint16_t zeros_skiped = *n;
    *row_index += *n;
    *n = 0;
    if(*row_index >= height){
        *n = *row_index - height;
        return zeros_skiped - *n;
    }
    return zeros_skiped;
}

uint16_t process_column(Matrix8_t *dstbuff, uint16_t buffer_index, BitIterator_t *bit_iterator, uint16_t rle_zeros, uint8_t bit_group){
    uint16_t row_index = 0;
    buffer_index += skip_n_zeros(&rle_zeros, &row_index, dstbuff->height);
    while(row_index < dstbuff->height){
        uint8_t pair = readBitPair(bit_iterator);
        if(pair == 0){
            rle_zeros += readRlePacket(bit_iterator);
            buffer_index += skip_n_zeros(&rle_zeros, &row_index, dstbuff->height);
        }
        else{
            dstbuff->arr[buffer_index] |= get_bit_group(bit_group, pair);
            buffer_index += 1;
            row_index += 1;
        }
    }
    return rle_zeros;
}

void picComp_decompressBitplane(Matrix8_t *dstbuff, BitIterator_t *bit_iterator){
    bool datapacketmode = get_next_bit(bit_iterator);
    uint16_t rle_zeros = 0;
    if(!datapacketmode){
        rle_zeros = readRlePacket(bit_iterator);
    }

    uint16_t buffer_index = 0;
    for(uint8_t row_subindex = 0; row_subindex < dstbuff->width; ++row_subindex){
        rle_zeros = process_column(dstbuff, buffer_index, bit_iterator, rle_zeros, 0b11);
        rle_zeros = process_column(dstbuff, buffer_index, bit_iterator, rle_zeros, 0b10);
        rle_zeros = process_column(dstbuff, buffer_index, bit_iterator, rle_zeros, 0b01);
        rle_zeros = process_column(dstbuff, buffer_index, bit_iterator, rle_zeros, 0b00);

        buffer_index += dstbuff->height;
    }
}
