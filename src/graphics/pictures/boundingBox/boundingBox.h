#pragma once
#ifndef GRAPHICS_PICTURES_BOUNDINGBOX_H
#define GRAPHICS_PICTURES_BOUNDINGBOX_H

#include <stddef.h>
#include <stdint.h>

#define LDPKSPR_BYTES_PER_TILE  8


void addBoundingBox(size_t buffer_size, uint8_t *buffer0, uint8_t *buffer1, uint8_t *buffer2, uint8_t bb_dimensions, size_t width_in_tiles, size_t height_in_tiles, size_t bytes_per_tile);


#endif /* GRAPHICS_PICTURES_BOUNDINGBOX_H */
