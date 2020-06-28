#include "bitplanes.h"


void mix_pair(uint8_t *dst_a, uint8_t *dst_b, uint8_t a, uint8_t b){
    uint8_t new_a = 0;
    uint8_t new_b = 0;
    for(size_t j = 0; j < 4; ++j){
        new_a <<= 2;
        new_a |= ((b >> (7-j)) & 0x1) << 1;
        new_a |= (a >> (7-j)) & 0x1;
    }
    for(size_t j = 4; j < 8; ++j){
        new_b <<= 2;
        new_b |= ((b >> (7-j)) & 0x1) << 1;
        new_b |= (a >> (7-j)) & 0x1;
    }
    *dst_a = new_a;
    *dst_b = new_b;
}

void mergeBitplanes(const size_t n, uint8_t buffer[n]){
    for(size_t i = 0; i+1 < n; i+=2){
        uint8_t new_a = 0;
        uint8_t new_b = 0;
        mix_pair(&new_a, &new_b, buffer[i], buffer[i+1]);
        buffer[i] = new_a;
        buffer[i+1] = new_b;
    }
}
