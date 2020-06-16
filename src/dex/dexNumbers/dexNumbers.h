#pragma once
#ifndef DEX_DEXNUMBERS_H
#define DEX_DEXNUMBERS_H

#include <stddef.h>
#include <stdint.h>

#define DEXNUMS_DEX_ORDER_PTR       0x41024


uint8_t dexNumById(const uint8_t *src_data, int64_t src_data_offset, uint8_t pkDex);


#endif /* DEX_DEXNUMBERS_H */
