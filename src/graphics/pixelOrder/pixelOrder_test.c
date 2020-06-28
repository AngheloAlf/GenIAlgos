#include "pixelOrder.h"

#include "utils/io/io.h"

#include <stdlib.h>


#define UNDERLINE(_text) "\e[4m"_text"\e[0m"
void check_arguments(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s %s %s\n", argv[0], UNDERLINE("sprite_in_row_order_file"), UNDERLINE("out_name"));
        exit(-1);
    }
}

int main(int argc, char **argv){
    check_arguments(argc, argv);
    const char *filename = argv[1];

    size_t tiles_per_row = 7;
    size_t tiles_per_column = 7;
    size_t bytes_per_tile = 8;
    size_t bits_per_pixel = 2;
    size_t size = tiles_per_row*bytes_per_tile*tiles_per_column*bytes_per_tile/(bytes_per_tile/bits_per_pixel);
    uint8_t *img_row_order = calloc(size, sizeof(uint8_t));
    readFile(img_row_order, size, filename, 0);

    uint8_t *img_col_order = calloc(size, sizeof(uint8_t));
    rowToColumnOrder(size, img_col_order, img_row_order, tiles_per_row, tiles_per_column, bytes_per_tile, bits_per_pixel);

    const char *out = argv[2];
    writeFile(img_col_order, size, out, 0);

    free(img_col_order);
    free(img_row_order);
    return 0;
}
