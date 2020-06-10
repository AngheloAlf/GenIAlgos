#include "toBmp.h"

#include <stdio.h>
#include <assert.h>

/// https://cdn.hackaday.io/files/274271173436768/Simplified%20Windows%20BMP%20Bitmap%20File%20Format%20Specification.htm


void write_1_byte(FILE *f, uint8_t val){
    fwrite(&val, 1, 1, f);
}
void write_2_bytes(FILE *f, uint16_t val){
    fwrite(&val, 2, 1, f);
}
void write_4_bytes(FILE *f, uint32_t val){
    fwrite(&val, 4, 1, f);
}


uint32_t offset_to_start(size_t bpp){
    return 14 + 40 + 4*MAX_COLORS(bpp);
}
uint32_t file_size(size_t bpp, uint32_t width, int32_t height){
    // TODO: Consider add support to 16, 24 and 32 bpp.
    const size_t bytes_per_row = width/PIXELS_PER_BYTE(bpp) + !!(width%(size_t)(PIXELS_PER_BYTE(bpp)));
    const uint32_t padding = (4 - (bytes_per_row % 4))%4;

    return offset_to_start(bpp) + (bytes_per_row + padding) * height;
}

void write_file_header(FILE *f, size_t bpp, uint32_t width, int32_t height){
    fwrite("BM", 1, 2, f); // bfType
    write_4_bytes(f, file_size(bpp, width, height)); // bfSize
    write_2_bytes(f, 0); // bfReserved1
    write_2_bytes(f, 0); // bfReserved2
    write_4_bytes(f, offset_to_start(bpp)); // bfOffBits
}


void write_image_header(FILE *f, size_t bpp, uint32_t width, int32_t height){
    const uint64_t header_size = 40;
    write_4_bytes(f, header_size); // biSize
    write_4_bytes(f, width); // biWidth
    write_4_bytes(f, height); // biHeight
    write_2_bytes(f, 1); // biPlanes
    write_2_bytes(f, bpp); // biBitCount

    write_4_bytes(f, 0); // biCompression
    write_4_bytes(f, 0); // biSizeImage
    write_4_bytes(f, 0); // biXPelsPerMeter
    write_4_bytes(f, 0); // biYPelsPerMeter
    write_4_bytes(f, 0); // biClrUsed
    write_4_bytes(f, 0); // biClrImportant
}

void write_color_table(FILE *f, size_t bpp, const uint32_t *colors){
    /// colors array must have at least (2**bpp) elements.
    /// color = [ZERO][RED][GREEN][BLUE]
    fwrite(colors, 4, MAX_COLORS(bpp), f);
}

void write_pixel_data(FILE *f, size_t arr_size, const uint8_t *in_arr, size_t bpp, uint32_t width, uint32_t height){
    const size_t pixels_per_byte = PIXELS_PER_BYTE(bpp);
    if(width % (4*pixels_per_byte) == 0){
        fwrite(in_arr, 1, arr_size, f);
        return;
    }

    const size_t bytes_per_row = width/pixels_per_byte + !!(width%pixels_per_byte);
    const uint32_t padding = (4 - (bytes_per_row % 4))%4;
    const uint32_t zero = 0;
    for(size_t i = 0; i < arr_size; i+=bytes_per_row){
        fwrite(&in_arr[i], 1, bytes_per_row, f);
        fwrite(&zero, padding, 1, f);
    }
}


void toBmp_bitIndexed(const char *out_file, size_t arr_size, const uint8_t *in_arr, size_t bpp, uint32_t width, int32_t height, const uint32_t *colors){
    assert(bpp <= 8);
    FILE *f = fopen(out_file, "wb");
    assert(f != NULL);
    write_file_header(f, bpp, width, height);
    write_image_header(f, bpp, width, height);
    write_color_table(f, bpp, colors);
    write_pixel_data(f, arr_size, in_arr, bpp, width, height);
    fclose(f);
}
