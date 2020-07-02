#include "picCompression.h"

#include <string.h>

#include "common/bitOperations/bitOperations.h"
#include "common/dataStructures/dataStructures.h"

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

    bool use_first_buffer = !BitIterator_nextBit(&compressed);

    picComp_decompressBitplane(use_first_buffer ? &buff0 : &buff1, &compressed);

    uint8_t decoding_mode = BitIterator_nextBit(&compressed);
    if(decoding_mode != 0){
        decoding_mode += BitIterator_nextBit(&compressed);
    }

    picComp_decompressBitplane(!use_first_buffer ? &buff0 : &buff1, &compressed);

    picComp_decodeBitplanes(&buff0, &buff1, false, decoding_mode, !use_first_buffer);
}
