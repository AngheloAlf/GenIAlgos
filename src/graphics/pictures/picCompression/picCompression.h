#pragma once
#ifndef GRAPHICS_PICTURES_PICCOMPRESSION_H
#define GRAPHICS_PICTURES_PICCOMPRESSION_H

#include "common/externalHeaders/externalHeaders.h"
#include "common/dataStructures/dataStructures.h"

void picComp_decompressBitplane(Matrix8_t *dstbuff, BitIterator_t *bit_iterator);
void picComp_decodeBitplanes(Matrix8_t *buffer_1, Matrix8_t *buffer_2, bool mirror, uint8_t interpret_mode, bool invert_buffers);

void picComp_decompressPicture(size_t dst_size, uint8_t dst_buffer0[dst_size], uint8_t dst_buffer1[dst_size], const uint8_t *compressed_arr);

#endif /* GRAPHICS_PICTURES_PICCOMPRESSION_H */
