#pragma once
#ifndef GRAPHICS_PIXELORDER_H
#define GRAPHICS_PIXELORDER_H

#include "common/externalHeaders/externalHeaders.h"

void rowToColumnOrder(size_t n, uint8_t dst_buffer[n], const uint8_t src_buffer[n], size_t tiles_per_row, size_t tiles_per_column, size_t bytes_per_tile, size_t bits_per_pixel);

#endif /* GRAPHICS_PIXELORDER_H */
