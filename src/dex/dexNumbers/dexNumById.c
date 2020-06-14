#include "dexNumbers.h"


uint8_t dexNumById(const uint8_t *src_data, int64_t src_data_offset, uint8_t pkDex){
    --pkDex;
    return src_data[DEXNUMS_DEX_ORDER_PTR + src_data_offset + pkDex];
}
