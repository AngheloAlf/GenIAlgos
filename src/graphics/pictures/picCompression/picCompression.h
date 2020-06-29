#pragma once
#ifndef GRAPHICS_PICTURES_PICCOMPRESSION_H
#define GRAPHICS_PICTURES_PICCOMPRESSION_H

#include "common/externalHeaders/externalHeaders.h"

void decompressPicture(size_t dst_size, uint8_t dst_buffer0[dst_size], uint8_t dst_buffer1[dst_size], const uint8_t *compressed_arr);

#endif /* GRAPHICS_PICTURES_PICCOMPRESSION_H */
