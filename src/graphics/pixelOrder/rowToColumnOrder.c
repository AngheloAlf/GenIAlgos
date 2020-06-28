#include "pixelOrder.h"


void rowToColumnOrder(size_t n, uint8_t dst_buffer[n], const uint8_t src_buffer[n], size_t tiles_per_row, size_t tiles_per_column, size_t bytes_per_tile, size_t bits_per_pixel){
    for(size_t i = 0; i+1 < n; i+=2){
        size_t j = (i%(bits_per_pixel*bytes_per_tile*tiles_per_column))*tiles_per_row;
        j += ((size_t)(i/(bits_per_pixel*bytes_per_tile*tiles_per_column)))*2;
        dst_buffer[j] = src_buffer[i];
        dst_buffer[j+1] = src_buffer[i+1];
    }
}
