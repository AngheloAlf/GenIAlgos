#include "picCompression.h"

#include <string.h>

#include "common/bitOperations/bitOperations.h"
#include "common/dataStructures/dataStructures.h"

uint8_t readBitPair(BitIterator_t *bit_iterator){
    uint8_t pair = BitIterator_nextBit(bit_iterator) << 1;
    return pair | BitIterator_nextBit(bit_iterator);
}

uint16_t readRlePacket(BitIterator_t *bit_iterator){
    uint16_t l = 0;
    size_t i = 1;
    while(BitIterator_nextBit(bit_iterator)){
        l |= 1;
        l <<= 1;
        ++i;
    }
    uint16_t v = 0;
    while(i--){
        v <<= 1;
        v |= BitIterator_nextBit(bit_iterator);
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
    bool datapacketmode = BitIterator_nextBit(bit_iterator);
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
