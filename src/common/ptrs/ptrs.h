#pragma once
#ifndef COMMON_PTRS_H
#define COMMON_PTRS_H

#include "common/externalHeaders/externalHeaders.h"

#define BANK_SIZE                       0x4000

uint32_t absolutePtr(uint8_t bank, uint16_t relative_ptr);
uint16_t ptrs_fetch16(const uint8_t *srcbuff, uint16_t high, uint16_t low);

#endif /* COMMON_PTRS_H */
