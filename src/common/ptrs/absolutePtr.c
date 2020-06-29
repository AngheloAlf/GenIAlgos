#include "ptrs.h"


uint32_t absolutePtr(uint8_t bank, uint16_t relative_ptr){
    if(relative_ptr < BANK_SIZE){
        return relative_ptr;
    }
    --bank;
    return bank*BANK_SIZE + relative_ptr;
}
