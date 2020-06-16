#include "dexInfo.h"


/// Includes delimiters.
size_t getEntriesLenByPtr(const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t entries_ptr){
    uint32_t ptr = ABSOLUTE_PTR(bank, entries_ptr);
    size_t len = 0;
    uint8_t val = 0;
    do{
        val = src_data[ptr + src_data_offset + len++];
    } while(val != END_OF_DATA);
    return len;
}
size_t getEntriesLenById(const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId){
    DexInfos_t aux;
    getDexInfoById_toStruct(&aux, src_data, src_data_offset, pkId);
    return getEntriesLenByPtr(src_data, src_data_offset, aux.dexEntryBank, aux.dexEntryPtr);
}

void getEntriesByPtr_toArr(size_t *dst_first_entry_len, uint8_t *dst_entries, const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t entries_ptr){
    size_t len = getEntriesLenByPtr(src_data, src_data_offset, bank, entries_ptr);
    uint32_t ptr = ABSOLUTE_PTR(bank, entries_ptr);
    for(size_t i = 0; i < len; ++i){
        dst_entries[i] = src_data[ptr + src_data_offset + i];
        if(dst_entries[i] == 0x49){
            *dst_first_entry_len = i+1;
        }
    }
}
void getEntriesById_toArr(size_t *dst_first_entry_len, uint8_t *dst_entries, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId){
    uint8_t bank;
    uint16_t infos_ptr = getDexInfosPtrById(&bank, src_data, src_data_offset, pkId);
    DexInfos_t dex_info;
    getDexInfoByPtr_toStruct(&dex_info, src_data, src_data_offset, bank, infos_ptr);
    getEntriesByPtr_toArr(dst_first_entry_len, dst_entries, src_data, src_data_offset, dex_info.dexEntryBank, dex_info.dexEntryPtr);
}
