#include "dataStructures.h"

#include "common/bitOperations/bitOperations.h"

uint8_t BitIterator_nextByte(BitIterator_t *bit_iterator){
    uint8_t byte = bit_iterator->bytes_arr[bit_iterator->byte_index];
    bit_iterator->byte_index += 1;
    return byte;
}
uint8_t BitIterator_nextBit(BitIterator_t *bit_iterator){
    if(bit_iterator->bit_index == 0){
        bit_iterator->actual_byte = BitIterator_nextByte(bit_iterator);
        bit_iterator->bit_index = 8;
    }
    bit_iterator->bit_index -= 1;
    bit_iterator->actual_byte = RLC(bit_iterator->actual_byte);
    return bit_iterator->actual_byte & 0b0001;
}
