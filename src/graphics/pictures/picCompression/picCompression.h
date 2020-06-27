#pragma once
#ifndef GRAPHICS_PICTURES_PICCOMPRESSION_H
#define GRAPHICS_PICTURES_PICCOMPRESSION_H

#include <stddef.h>
#include <stdint.h>


void decompressPicture(size_t dst_size, uint8_t *dst_buffer0, uint8_t *dst_buffer1, size_t compressed_size, /*const */uint8_t *compressed_arr);


#endif /* GRAPHICS_PICTURES_PICCOMPRESSION_H */
