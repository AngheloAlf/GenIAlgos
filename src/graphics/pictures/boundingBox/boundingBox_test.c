#include "boundingBox.h"

#include "utils/io/io.h"
#include "utils/text/text.h"

#include <stdio.h>
#include <stdlib.h>

#define BYTES_PER_TILE  8
#define WIDTH_IN_TILES  7
#define HEIGHT_IN_TILES 7

#define BUFF_SIZE       WIDTH_IN_TILES*HEIGHT_IN_TILES*BYTES_PER_TILE

void check_arguments(int argc, char **argv){
    if(argc < 2){
        printf("Usage: %s %s\n", argv[0], UNDERLINE("sprite_file"));
        exit(-1);
    }
}

int main(int argc, char **argv){
    check_arguments(argc, argv);
    const char *filename = argv[1];

    uint8_t full_buffer[3*BUFF_SIZE];

    uint8_t *buffer0 = &full_buffer[0*BUFF_SIZE];
    uint8_t *buffer1 = &full_buffer[1*BUFF_SIZE];
    uint8_t *buffer2 = &full_buffer[2*BUFF_SIZE];

    readFile(&full_buffer[1*BUFF_SIZE], 2*BUFF_SIZE, filename, 0);

    addBoundingBox(BUFF_SIZE, buffer0, buffer1, buffer2, 0x55, WIDTH_IN_TILES, HEIGHT_IN_TILES, BYTES_PER_TILE);

    writeFile(&full_buffer[1*BUFF_SIZE], 2*BUFF_SIZE, "bb_out.bin", 0);

    return 0;
}
