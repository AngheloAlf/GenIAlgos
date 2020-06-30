#include "ptrs.h"

uint16_t ptrs_fetch16(const uint8_t *srcbuff, uint16_t high, uint16_t low){
    uint8_t data_low = srcbuff[low];
    uint8_t data_high = srcbuff[high];
    return (data_high << 8) | data_low;
}
