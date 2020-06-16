#include "dexInfo.h"


void getDexInfoByPtr_toArr(uint8_t *dst_arr, const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t infos_ptr){
    uint32_t ptr = ABSOLUTE_PTR(bank, infos_ptr);
    size_t len = getSpiciesNameLenByPtr(src_data, src_data_offset, bank, infos_ptr);

    for(size_t i = 0; i < 0x09; ++i){
        dst_arr[i] = src_data[ptr + src_data_offset + len + i];
    }
}
void getDexInfoById_toArr(uint8_t *dst_arr, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId){
    uint8_t bank;
    uint16_t infos_ptr = getDexInfosPtrById(&bank, src_data, src_data_offset, pkId);
    getDexInfoByPtr_toArr(dst_arr, src_data, src_data_offset, bank, infos_ptr);
}

void getDexInfoByPtr_toStruct(DexInfos_t *dst_stru, const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t infos_ptr){
    uint8_t dst_arr[0x09];
    getDexInfoByPtr_toArr(dst_arr, src_data, src_data_offset, bank, infos_ptr);

    dst_stru->feet = dst_arr[0x00];
    dst_stru->inches = dst_arr[0x01];
    dst_stru->weight = dst_arr[0x02] | (dst_arr[0x03] << 8);
    dst_stru->always0x17 = dst_arr[0x04];
    dst_stru->dexEntryPtr = dst_arr[0x05] | (dst_arr[0x06] << 8);
    dst_stru->dexEntryBank = dst_arr[0x07];
    dst_stru->endOfData = dst_arr[0x08];
}
void getDexInfoById_toStruct(DexInfos_t *dst_stru, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId){
    uint8_t bank;
    uint16_t infos_ptr = getDexInfosPtrById(&bank, src_data, src_data_offset, pkId);
    getDexInfoByPtr_toStruct(dst_stru, src_data, src_data_offset, bank, infos_ptr);
}
