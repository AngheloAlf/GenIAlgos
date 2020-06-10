#pragma once
#ifndef TOBMP_H
#define TOBMP_H

#include <stddef.h>
#include <stdint.h>

#define MAX_COLORS(_bpp)        (1 << (_bpp))
#define PIXELS_PER_BYTE(_bpp)   (8/(_bpp))


void toBmp_bitIndexed(const char *out_file, size_t arr_size, const uint8_t *in_arr, size_t bpp, uint32_t width, int32_t height, const uint32_t *colors);

#endif /* TOBMP_H */
