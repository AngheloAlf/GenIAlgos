#include "common/externalHeaders/externalHeaders.h"
#include "common/ptrs/ptrs.h"

#include "dex/dexNumbers/dexNumbers.h"
#include "pk/names/names.h"
#include "text/toAscii/toAscii.h"
#include "graphics/pictures/bankSwitch/bankSwitch.h"
#include "dex/dexInfo/dexInfo.h"
#include "pk/stats/stats.h"
#include "graphics/pictures/picCompression/picCompression.h"
#include "graphics/pictures/boundingBox/boundingBox.h"
#include "graphics/bitplanes/bitplanes.h"
#include "graphics/pixelOrder/pixelOrder.h"
#include "utils/image/bmp/bmp.h"
#include "utils/io/io.h"
#include "utils/numbers/numbers.h"

#include <stdlib.h>
#include <inttypes.h>

#define UNDERLINE(_text) "\e[4m"_text"\e[0m"
void check_arguments(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s %s %s\n", argv[0], UNDERLINE("rom_file"), UNDERLINE("pk_id"));
        exit(-1);
    }
}

#define BUFFER_SIZE     0x188

void get_pk_name(size_t n, char dst_name[n], const uint8_t *rom, uint8_t pk_id){
    uint8_t pk_name[PKNAMES_NAME_LEN];
    pkNames_getNameById(pk_name, rom, 0, pkNames_namesPtr(rom, 0), pk_id);
    text_toAsciiStr(dst_name, text_lenAsAscii(PKNAMES_NAME_LEN, pk_name), pk_name);
    dst_name[n-1] = 0;
}

void make_outfile_name(size_t n, char dst_name[n], uint8_t pk_id, uint8_t dex_num, const char *pk_name, const char *extra){
    int chars_written = snprintf(dst_name, n, "%03"PRId8" - 0x%02"PRIX8" - %s - %s.bmp", dex_num, pk_id, pk_name, extra);
    if(chars_written < 0){
        fprintf(stderr, "snprintf error");
        exit(-1);
    }
    dst_name[chars_written] = 0;
}

void get_pic_ptrs(uint8_t *dimFront, uint32_t *frontPtr, uint32_t *backPtr, const uint8_t *rom, uint8_t pk_id, uint8_t dex_num){
    PkSpeciesStats_t specie_data;
    pkStats_byDexToStruct(&specie_data, rom, 0, dex_num);
    *dimFront = specie_data.spritePtrs.dimFrontSprite;

    size_t bank = getRBankByPkId(pk_id, false);
    printf("bank: 0x%zu\n", bank);

    printf("frontSpritePtr: 0x%04"PRIX16"\n", specie_data.spritePtrs.frontSpritePtr);
    *frontPtr = absolutePtr(bank, specie_data.spritePtrs.frontSpritePtr);

    printf("backSpritePtr:  0x%04"PRIX16"\n", specie_data.spritePtrs.backSpritePtr);
    *backPtr = absolutePtr(bank, specie_data.spritePtrs.backSpritePtr);
}

void extract_picture(uint8_t dst_buffer[2*BUFFER_SIZE], const uint8_t *picture_buff, uint8_t bounding_box_size, size_t tiles_per_row, size_t tiles_per_column, size_t bytes_per_tile, size_t bits_per_pixel){
    uint8_t buffer[30*BUFFER_SIZE];
    uint8_t *buffer0 = &buffer[0*BUFFER_SIZE];
    uint8_t *buffer1 = &buffer[1*BUFFER_SIZE];
    uint8_t *buffer2 = &buffer[2*BUFFER_SIZE];

    decompressPicture(BUFFER_SIZE, buffer1, buffer2, picture_buff);

    addBoundingBox(BUFFER_SIZE, buffer0, buffer1, buffer2, bounding_box_size, tiles_per_row, tiles_per_column, bytes_per_tile);
    mergeBitplanes(2*BUFFER_SIZE, buffer1);

    rowToColumnOrder(2*BUFFER_SIZE, dst_buffer, buffer1, tiles_per_row, tiles_per_column, bytes_per_tile, bits_per_pixel);
}

void make_image(char *out_name, uint8_t *image_buff, const uint32_t *colors, size_t tiles_per_row, size_t tiles_per_column, size_t bytes_per_tile, size_t bits_per_pixel){
    const uint32_t width = bytes_per_tile*tiles_per_row;
    const int32_t height = bytes_per_tile*tiles_per_column;
    toBmp_bitIndexed(out_name, 2*BUFFER_SIZE, image_buff, bits_per_pixel, width, -height, colors);
}

void extract_pic(const uint8_t *rom, uint8_t pk_id){
    size_t tiles_per_row = 7;
    size_t tiles_per_column = 7;
    size_t bytes_per_tile = 8;
    size_t bits_per_pixel = 2;

    printf("pk_id: 0x%02"PRIX8"\n", pk_id);

    uint8_t dex_num = dexNumById(rom, 0, pk_id);
    printf("dex_num: 0x%02"PRIX8"\n", dex_num);

    char pk_name[64];
    get_pk_name(64, pk_name, rom, pk_id);
    printf("name: %s\n", pk_name);

    char front_name[1024+1];
    make_outfile_name(1024, front_name, pk_id, dex_num, pk_name, "front");
    char back_name[1024+1];
    make_outfile_name(1024, back_name, pk_id, dex_num, pk_name, "back");

    uint8_t dimFront;
    uint32_t frontPtr, backPtr;
    get_pic_ptrs(&dimFront, &frontPtr, &backPtr, rom, pk_id, dex_num);
    printf("dimFrontSprite: 0x%02"PRIX8"\n", dimFront);
    printf("frontPtr:       0x%"PRIX32"\n", frontPtr);
    printf("backPtr:        0x%"PRIX32"\n", backPtr);

    uint8_t front[2*BUFFER_SIZE];
    uint8_t back[2*BUFFER_SIZE];
    extract_picture(front, &rom[frontPtr], dimFront, tiles_per_row, tiles_per_column, bytes_per_tile, bits_per_pixel);
    extract_picture(back, &rom[backPtr], 0x44, tiles_per_row, tiles_per_column, bytes_per_tile, bits_per_pixel);

    const uint32_t colors[4] = {3*(0xFFFFFF/3), 2*(0xFFFFFF/3), 1*(0xFFFFFF/3), 0};
    //const uint32_t colors[4] = {0xFFFFFF, 0x1E1611*8, 0x100E13*8, 0};
    printf("front image: %s\n", front_name);
    make_image(front_name, front, colors, tiles_per_row, tiles_per_column, bytes_per_tile, bits_per_pixel);
    printf("back image: %s\n", back_name);
    make_image(back_name, back, colors, tiles_per_row, tiles_per_column, bytes_per_tile, bits_per_pixel);
    printf("\n");
}

int main(int argc, char **argv){
    check_arguments(argc, argv);

    const char *filename = argv[1];
    size_t rom_size = getFileSize(filename);
    uint8_t *rom = calloc(rom_size, sizeof(uint8_t));
    readFile(rom, rom_size, filename, 0);

    uint8_t pk_id = strToNumber(argv[2]);

    extract_pic(rom, pk_id);

    free(rom);
    return 0;
}
