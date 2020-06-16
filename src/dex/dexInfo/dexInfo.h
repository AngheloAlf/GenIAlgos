#pragma once
#ifndef DEX_DEXINFO_H
#define DEX_DEXINFO_H

#include <stddef.h>
#include <stdint.h>

#define BANK_SIZE                       0x4000
#define ABSOLUTE_PTR(_bank, _rel_ptr)   ((_bank-1)*BANK_SIZE + _rel_ptr)

#define END_OF_DATA         0x50

#define DEXINFO_INFOS_PTR       0x447E
#define DEXINFO_INFOS_PTR_BANK  0x10
#define DEXINFO_INFOS_PTR_ABSO  ABSOLUTE_PTR(DEXINFO_INFOS_PTR_BANK, DEXINFO_INFOS_PTR)

typedef struct{
    uint8_t feet;
    uint8_t inches;
    uint16_t weight;
    uint8_t always0x17;
    uint16_t dexEntryPtr;
    uint8_t dexEntryBank;
    uint8_t endOfData;
} DexInfos_t;


uint16_t getDexInfosPtrById(uint8_t *dst_bank_id, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId);

/// Includes the END_OF_DATA character
size_t getSpiciesNameLenByPtr(const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t infos_ptr);
size_t getSpiciesNameLenById(const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId);
void getSpeciesNameByPtr(uint8_t *dst_specie_name, const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t infos_ptr);
void getSpeciesNameById(uint8_t *dst_specie_name, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId);

void getDexInfoByPtr_toArr(uint8_t *dst_arr, const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t infos_ptr);
void getDexInfoById_toArr(uint8_t *dst_arr, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId);
void getDexInfoByPtr_toStruct(DexInfos_t *dst_stru, const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t infos_ptr);
void getDexInfoById_toStruct(DexInfos_t *dst_stru, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId);

/// Includes delimiters.
size_t getEntriesLenByPtr(const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t entries_ptr);
size_t getEntriesLenById(const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId);
void getEntriesByPtr_toArr(size_t *dst_first_entry_len, uint8_t *dst_entries, const uint8_t *src_data, int64_t src_data_offset, uint8_t bank, uint16_t entries_ptr);
void getEntriesById_toArr(size_t *dst_first_entry_len, uint8_t *dst_entries, const uint8_t *src_data, int64_t src_data_offset, uint8_t pkId);


#endif /* DEX_DEXINFO_H */
