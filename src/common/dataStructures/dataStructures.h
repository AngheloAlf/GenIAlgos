#pragma once
#ifndef COMMON_DATASTRUCTURES_H
#define COMMON_DATASTRUCTURES_H

#include "common/externalHeaders/externalHeaders.h"

typedef struct{
    size_t size;
    uint8_t *arr;
} Array8_t;

typedef struct{
    size_t size;
    uint8_t *arr;
    size_t width, height;
} Matrix8_t;

typedef struct{
    uint8_t *bytes_arr;
    uint16_t byte_index;
    uint8_t bit_index;
    uint8_t actual_byte;
} BitIterator_t;

#endif /* COMMON_DATASTRUCTURES_H */
