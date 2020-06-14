#include "bmp.h"

#include <stdio.h>
#include <assert.h>


void write_1_byte(FILE *f, uint8_t val){
    fwrite(&val, 1, 1, f);
}
void write_2_bytes(FILE *f, uint16_t val){
    fwrite(&val, 2, 1, f);
}
void write_4_bytes(FILE *f, uint32_t val){
    fwrite(&val, 4, 1, f);
}

typedef struct{
    size_t array_size;
    const uint8_t *raw_array;
    size_t bpp;
    uint32_t width, height;
    const uint32_t *colors;
} RawBitIndexedImg;


uint32_t offset_to_start(const RawBitIndexedImg *img_data){
    return 14 + 40 + 4*MAX_COLORS(img_data->bpp);
}
uint32_t file_size(const RawBitIndexedImg *img_data){
    // TODO: Consider add support to 16, 24 and 32 bpp.
    const size_t bytes_per_row = img_data->width/PIXELS_PER_BYTE(img_data->bpp) + !!(img_data->width%PIXELS_PER_BYTE(img_data->bpp));
    const uint32_t padding = BMP_BYTES_PADDING(bytes_per_row);

    return offset_to_start(img_data) + (bytes_per_row + padding) * img_data->height;
}

void write_file_header(FILE *f, const RawBitIndexedImg *img_data){
    fwrite("BM", 1, 2, f); // bfType
    write_4_bytes(f, file_size(img_data)); // bfSize
    write_2_bytes(f, 0); // bfReserved1
    write_2_bytes(f, 0); // bfReserved2
    write_4_bytes(f, offset_to_start(img_data)); // bfOffBits
}


void write_image_header(FILE *f, const RawBitIndexedImg *img_data){
    const uint64_t header_size = 40;
    write_4_bytes(f, header_size); // biSize
    write_4_bytes(f, img_data->width); // biWidth
    write_4_bytes(f, img_data->height); // biHeight
    write_2_bytes(f, 1); // biPlanes
    write_2_bytes(f, img_data->bpp); // biBitCount

    write_4_bytes(f, 0); // biCompression
    write_4_bytes(f, 0); // biSizeImage
    write_4_bytes(f, 0); // biXPelsPerMeter
    write_4_bytes(f, 0); // biYPelsPerMeter
    write_4_bytes(f, 0); // biClrUsed
    write_4_bytes(f, 0); // biClrImportant
}

void write_color_table(FILE *f, const RawBitIndexedImg *img_data){
    /// colors array must have at least (2**bpp) elements.
    /// color = [ZERO][RED][GREEN][BLUE]
    fwrite(img_data->colors, 4, MAX_COLORS(img_data->bpp), f);
}

void write_pixel_data(FILE *f, const RawBitIndexedImg *img_data){
    const size_t pixels_per_byte = PIXELS_PER_BYTE(img_data->bpp);
    if(img_data->width % (BMP_BYTE_BOUNDARY*pixels_per_byte) == 0){
        fwrite(img_data->raw_array, 1, img_data->array_size, f);
        return;
    }

    const size_t bytes_per_row = img_data->width/pixels_per_byte + !!(img_data->width%pixels_per_byte);
    const uint32_t padding = BMP_BYTES_PADDING(bytes_per_row);
    const uint32_t zero = 0;
    for(size_t i = 0; i < img_data->array_size; i+=bytes_per_row){
        fwrite(&img_data->raw_array[i], 1, bytes_per_row, f);
        fwrite(&zero, padding, 1, f);
    }
}


void toBmp_bitIndexed(const char *out_file, size_t arr_size, const uint8_t *in_arr, size_t bpp, uint32_t width, int32_t height, const uint32_t *colors){
    assert(bpp <= 8);
    FILE *f = fopen(out_file, "wb");
    assert(f != NULL);

    RawBitIndexedImg image = {
        .array_size = arr_size,
        .raw_array = in_arr,
        .bpp = bpp,
        .width = width,
        .height = height,
        .colors = colors
    };

    write_file_header(f, &image);
    write_image_header(f, &image);
    write_color_table(f, &image);
    write_pixel_data(f, &image);
    fclose(f);
}
