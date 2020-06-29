#pragma once
#ifndef UTILS_IMAGE_BMP_H
#define UTILS_IMAGE_BMP_H

#include "common/externalHeaders/externalHeaders.h"

#define MAX_COLORS(_bpp)                    (1 << (_bpp))
#define PIXELS_PER_BYTE(_bpp)               (8/(_bpp))

#define BMP_BYTE_BOUNDARY                   4
#define BMP_BYTES_PADDING(_bytes_per_row)   ((BMP_BYTE_BOUNDARY - ((_bytes_per_row) % BMP_BYTE_BOUNDARY))%BMP_BYTE_BOUNDARY)

void toBmp_bitIndexed(const char *out_file, size_t arr_size, const uint8_t *in_arr, size_t bpp, uint32_t width, int32_t height, const uint32_t *colors);

#endif /* UTILS_IMAGE_BMP_H */
