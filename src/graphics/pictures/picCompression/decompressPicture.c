#include "picCompression.h"

#include <string.h>

static uint8_t RLC(uint8_t number){
    return ((number & 0b01111111) << 1) | ((number & 0b10000000) >> 7);
}
/*
static uint8_t RRC(uint8_t number){
    return ((number & 0b11111110) >> 1) | ((number & 0b00000001) << 7);
}*/
static uint8_t SWAP(uint8_t number){
    return ((number & 0x0F) << 4) | ((number & 0xF0) >> 4);
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

void picComp_decompressPicture(size_t dst_size, uint8_t dst_buffer0[dst_size], uint8_t dst_buffer1[dst_size], const uint8_t *compressed_arr){
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
        .bytes_arr = (uint8_t *)&compressed_arr[1],
        .byte_index = 0,
        .bit_index = 0,
        .actual_byte = 0
    };

    // clean_buffers
    memset(buff0.arr, 0, buff0.size);
    memset(buff1.arr, 0, buff1.size);

    bool use_first_buffer = !get_next_bit(&compressed);

    picComp_decompressBitplane(use_first_buffer ? &buff0 : &buff1, &compressed);

    uint8_t decoding_mode = get_next_bit(&compressed);
    if(decoding_mode != 0){
        decoding_mode += get_next_bit(&compressed);
    }

    picComp_decompressBitplane(!use_first_buffer ? &buff0 : &buff1, &compressed);

    picComp_decodeBitplanes(&buff0, &buff1, false, decoding_mode, !use_first_buffer);
}
