#include "names.h"

#include "common/ptrs/ptrs.h"

#include <string.h>

uint32_t pkNames_namesPtr(const uint8_t *src_data, int64_t src_data_offset){
    uint16_t ptr = src_data[PKNAMES_PTR_TO_NAMES_LOW + src_data_offset];
    ptr |= src_data[PKNAMES_PTR_TO_NAMES_HIGH + src_data_offset]<<8;
    return absolutePtr(PKNAMES_BANK, ptr);
}

void pkNames_getNameById(uint8_t dst_buff[PKNAMES_NAME_LEN], const uint8_t *src_data, int64_t src_data_offset, uint32_t names_ptr, uint8_t pk_id){
    --pk_id;
    names_ptr += pk_id*PKNAMES_NAME_LEN + src_data_offset;
    memmove(dst_buff, &src_data[names_ptr], PKNAMES_NAME_LEN);
}
