#include "bitOperations.h"

uint8_t RLC(uint8_t number){
    return ((number & 0b01111111) << 1) | ((number & 0b10000000) >> 7);
}
uint8_t RRC(uint8_t number){
    return ((number & 0b11111110) >> 1) | ((number & 0b00000001) << 7);
}

uint8_t SWAP(uint8_t number){
    return ((number & 0x0F) << 4) | ((number & 0xF0) >> 4);
}

uint8_t BIT(uint8_t number, uint8_t bit_i){
    return (number >> bit_i) & 0x01;
}
