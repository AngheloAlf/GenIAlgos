#include "boundingBox.h"

#include <inttypes.h>
#include <assert.h>

typedef struct{
    size_t size;
    uint8_t *arr;
    size_t width, height;
} Matrix8_t;


static uint8_t calculate_offset(uint8_t width_in_tiles, uint8_t height_in_tiles, uint8_t bb_width, uint8_t bb_height, uint8_t bytes_per_tile){
    uint8_t y = height_in_tiles - bb_height;
    uint8_t x = (width_in_tiles - bb_width + 1)/2;
    uint8_t offset = height_in_tiles * x + y;
    return bytes_per_tile * offset;
}

static void process_bounding_box(Matrix8_t *dst_buffer, const Matrix8_t *src_buffer, size_t bb_width, size_t bb_height, size_t bytes_per_tile){
    for(size_t i = 0; i < dst_buffer->size; ++i){
        dst_buffer->arr[i] = 0;
    }

    size_t src_i = 0;
    size_t dst_offset = calculate_offset(dst_buffer->width, dst_buffer->height, bb_width, bb_height, bytes_per_tile);
    for(size_t row = 0; row < bb_width; ++row){
        for(size_t col_j = 0; col_j < bb_height*bytes_per_tile; ++col_j){
            dst_buffer->arr[col_j + dst_offset] = src_buffer->arr[src_i];
            ++src_i;
        }
        dst_offset += dst_buffer->height*bytes_per_tile;
    }
}

static void zip_bitplanes(Matrix8_t *dst_buffer0, Matrix8_t *dst_buffer1, const Matrix8_t *bitplane0, const Matrix8_t *bitplane1){
    size_t plane_index = bitplane0->size-1;
    for(long long i = dst_buffer1->size-1; i > 0; i-=2){
        dst_buffer1->arr[i] = bitplane1->arr[plane_index];
        dst_buffer1->arr[i-1] = bitplane0->arr[plane_index];
        --plane_index;
    }
    for(long long i = dst_buffer0->size-1; i > 0; i-=2){
        dst_buffer0->arr[i] = bitplane1->arr[plane_index];
        dst_buffer0->arr[i-1] = bitplane0->arr[plane_index];
        --plane_index;
    }
}


void addBoundingBox(size_t buffer_size, uint8_t *buffer0, uint8_t *buffer1, uint8_t *buffer2, uint8_t bb_dimensions, size_t width_in_tiles, size_t height_in_tiles, size_t bytes_per_tile){
    /// The three buffers must have the same size.
    Matrix8_t buff0 = {
        .size = buffer_size,
        .arr = buffer0,
        .width = width_in_tiles,
        .height = height_in_tiles
    };
    Matrix8_t buff1 = {
        .size = buffer_size,
        .arr = buffer1,
        .width = width_in_tiles,
        .height = height_in_tiles
    };
    Matrix8_t buff2 = {
        .size = buffer_size,
        .arr = buffer2,
        .width = width_in_tiles,
        .height = height_in_tiles
    };

    size_t bb_width, bb_height;
    bb_width  = (bb_dimensions & 0b00001111);
    bb_height = (bb_dimensions & 0b11110000) >> 4;

    process_bounding_box(&buff0, &buff1, bb_width, bb_height, bytes_per_tile);
    process_bounding_box(&buff1, &buff2, bb_width, bb_height, bytes_per_tile);

    zip_bitplanes(&buff1, &buff2, &buff0, &buff1);
}
