#include "names.h"

#include "common/ptrs/ptrs.h"

void pkNames_getNameById(uint8_t dst_buff[PKNAMES_NAME_LEN], const uint8_t *src_data, int64_t src_data_offset, uint8_t pk_id){
    --pk_id;
    uint16_t names_rel_ptr = src_data[PKNAMES_PTR_TO_NAMES_LOW + src_data_offset];
    names_rel_ptr |= src_data[PKNAMES_PTR_TO_NAMES_HIGH + src_data_offset]<<8;
    uint32_t names_ptr = absolutePtr(PKNAMES_BANK, names_rel_ptr);
    names_ptr += pk_id*PKNAMES_NAME_LEN;
    for(size_t i = 0; i < PKNAMES_NAME_LEN; ++i){
        dst_buff[i] = src_data[names_ptr + i];
    }
}
