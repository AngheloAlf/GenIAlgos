#include "dexInfo.h"

uint16_t getDexInfosPtrById(uint8_t *dst_bank_id, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId){
    --pkId;
    *dst_bank_id = DEXINFO_INFOS_PTR_BANK;
    uint8_t first_byte = src_data[DEXINFO_INFOS_PTR_ABSO + src_data_offset + 2*pkId];
    uint8_t second_byte = src_data[DEXINFO_INFOS_PTR_ABSO + src_data_offset + 2*pkId + 1];
    uint16_t ptr = (second_byte<<8) | first_byte;
    return ptr;
}
