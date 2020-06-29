#include "dexInfo.h"

/// Includes the END_OF_DATA character
size_t getSpiciesNameLenByPtr(const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t infos_ptr){
    uint32_t ptr = absolutePtr(bank, infos_ptr);
    size_t len = 0;
    uint8_t val = 0;
    do{
        val = src_data[ptr + src_data_offset + len++];
    } while(val != END_OF_DATA);
    return len;
}
size_t getSpiciesNameLenById(const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId){
    uint8_t bank;
    uint16_t infos_ptr = getDexInfosPtrById(&bank, src_data, src_data_offset, pkId);
    return getSpiciesNameLenByPtr(src_data, src_data_offset, bank, infos_ptr);
}

void getSpeciesNameByPtr(uint8_t *dst_specie_name, const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t infos_ptr){
    uint32_t ptr = absolutePtr(bank, infos_ptr);
    size_t len = getSpiciesNameLenByPtr(src_data, src_data_offset, bank, infos_ptr);
    for(size_t i = 0; i < len; ++i){
        dst_specie_name[i] = src_data[ptr + src_data_offset + i];
    }
}
void getSpeciesNameById(uint8_t *dst_specie_name, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId){
    uint8_t bank;
    uint16_t infos_ptr = getDexInfosPtrById(&bank, src_data, src_data_offset, pkId);
    getSpeciesNameByPtr(dst_specie_name, src_data, src_data_offset, bank, infos_ptr);
}
