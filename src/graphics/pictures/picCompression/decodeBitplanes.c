#include "picCompression.h"

#include <string.h>
#include <assert.h>

static uint8_t SWAP(uint8_t number){
    return ((number & 0x0F) << 4) | ((number & 0xF0) >> 4);
}
static uint8_t BIT(uint8_t number, uint8_t bit_i){
    return (number >> bit_i) & 0x01;
}

uint8_t delta_decode_byte(uint8_t byte, uint8_t *last_bit, bool mirror){
    assert(*last_bit < 2);
    uint8_t decoded = 0;
    for(int i = 7; i >= 0; --i){
        if((byte >> i) & 0x01){
            *last_bit = 1 - *last_bit;
        }
        if(!mirror){
            decoded <<= 1;
            decoded |= *last_bit;
        }
        else{
            decoded >>= 1;
            decoded |= (*last_bit) << 7;
        }
    }

    if(mirror){
        return SWAP(decoded);
    }
    return decoded;
}

void delta_decode_row(Matrix8_t *dstbuf, bool mirror, uint16_t buffer_index){
    uint8_t last_bit = 0;
    for(uint8_t i = 0; i < dstbuf->width; ++i){
        dstbuf->arr[buffer_index] = delta_decode_byte(dstbuf->arr[buffer_index], &last_bit, mirror);
        buffer_index += dstbuf->height;
    }
}

void delta_decode(Matrix8_t *dstbuf, bool mirror){
    uint16_t buffer_index = 0;
    for(uint8_t i = 0; i < dstbuf->height; ++i){
        delta_decode_row(dstbuf, mirror, buffer_index);
        buffer_index += 1;
    }
}

uint8_t mirror_nibble(uint8_t nibble){
    uint8_t mirrored = 0;
    for(size_t i = 0; i < 4; ++i){
        mirrored |= BIT(nibble, i) << (3-i);
    }
    return mirrored;
}

uint8_t mirror_both_nibbles(uint8_t byte){
    uint8_t high_n = mirror_nibble(byte >> 4) << 4;
    return high_n | mirror_nibble(byte & 0x0f);
}

void xor_to_buff(Matrix8_t *dstbuf, Matrix8_t *otherbuf, bool mirror){
    uint16_t buffer_index = 0;
    for(uint8_t i = 0; i < dstbuf->width; ++i){
        for(uint8_t j = 0; j < dstbuf->height; ++j){
            if(mirror){
                dstbuf->arr[buffer_index] = mirror_both_nibbles(dstbuf->arr[buffer_index]);
            }
            dstbuf->arr[buffer_index] ^= otherbuf->arr[buffer_index];
            buffer_index += 1;
        }
    }
}

void decode_mode_0(Matrix8_t *buffer_1, Matrix8_t *buffer_2, bool mirror){
    delta_decode(buffer_2, mirror);
    delta_decode(buffer_1, mirror);
}
void decode_mode_1(Matrix8_t *buffer_1, Matrix8_t *buffer_2, bool mirror){
    delta_decode(buffer_1, mirror);
    xor_to_buff(buffer_2, buffer_1, mirror);
}
void decode_mode_2(Matrix8_t *buffer_1, Matrix8_t *buffer_2, bool mirror){
    delta_decode(buffer_2, false);
    delta_decode(buffer_1, mirror);
    xor_to_buff(buffer_2, buffer_1, mirror);
}

static void (*const decode_modes[3])(Matrix8_t *, Matrix8_t *, bool) = {
    decode_mode_0, decode_mode_1, decode_mode_2
};

void picComp_decodeBitplanes(Matrix8_t *buffer_1, Matrix8_t *buffer_2, bool mirror, uint8_t decoding_mode, bool invert_buffers){
    assert(decoding_mode <= 2);
    if(invert_buffers){
        decode_modes[decoding_mode](buffer_2, buffer_1, mirror);
        return;
    }
    decode_modes[decoding_mode](buffer_1, buffer_2, mirror);
}
