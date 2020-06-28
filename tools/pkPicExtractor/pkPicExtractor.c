#include "dex/dexNumbers/dexNumbers.h"
#include "pointers/pkSpeciesStats/pkStatsByDex.h"
#include "graphics/pictures/bankSwitch/bankSwitch.h"
#include "dex/dexInfo/dexInfo.h"
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
    if(argc < 4){
        printf("Usage: %s %s %s %s\n", argv[0], UNDERLINE("rom_file"), UNDERLINE("pk_id"), UNDERLINE("out_name"));
        exit(-1);
    }
}

#define BUFFER_SIZE     0x188

int main(int argc, char **argv){
    check_arguments(argc, argv);

    const char *filename = argv[1];
    size_t rom_size = getFileSize(filename);
    uint8_t *rom = calloc(rom_size, sizeof(uint8_t));
    readFile(rom, rom_size, filename, 0);

    uint8_t pk_id = strToNumber(argv[2]);
    printf("pk_id: 0x%02"PRIX8"\n", pk_id);

    uint8_t dex_num = dexNumById(rom, 0, pk_id);
    printf("dex_num: 0x%02"PRIX8"\n", dex_num);
    PkSpeciesStats_t specie_data;
    load_pk_stats_by_dex_to_struct(&specie_data, rom, 0, dex_num);
    size_t bank = getRBankByPkId(pk_id, false);
    printf("bank: 0x%zu\n", bank);

    uint8_t buffer[30*BUFFER_SIZE];
    uint8_t *buffer0 = &buffer[0*BUFFER_SIZE];
    uint8_t *buffer1 = &buffer[1*BUFFER_SIZE];
    uint8_t *buffer2 = &buffer[2*BUFFER_SIZE];

    printf("frontSpritePtr: 0x%04"PRIX16"\n", specie_data.spritePtrs.frontSpritePtr);
    printf("absolute_ptr: 0x%zx\n", ABSOLUTE_PTR(bank, specie_data.spritePtrs.frontSpritePtr));
    decompressPicture(BUFFER_SIZE, buffer1, buffer2, specie_data.spritePtrs.backSpritePtr-specie_data.spritePtrs.frontSpritePtr, &rom[ABSOLUTE_PTR(bank, specie_data.spritePtrs.frontSpritePtr)]);

    free(rom);

    size_t tiles_per_row = 7;
    size_t tiles_per_column = 7;
    size_t bytes_per_tile = 8;
    size_t bits_per_pixel = 2;

;
    printf("dimFrontSprite: 0x%02"PRIX8"\n", specie_data.spritePtrs.dimFrontSprite);
    addBoundingBox(BUFFER_SIZE, buffer0, buffer1, buffer2, specie_data.spritePtrs.dimFrontSprite, tiles_per_row, tiles_per_column, bytes_per_tile);
    mergeBitplanes(2*BUFFER_SIZE, buffer1);
    uint8_t final_buffer[2*BUFFER_SIZE];
    rowToColumnOrder(2*BUFFER_SIZE, final_buffer, buffer1, tiles_per_row, tiles_per_column, bytes_per_tile, bits_per_pixel);

    const char *out = argv[3];
    const uint32_t colors[4] = {3*(0xFFFFFF/3), 2*(0xFFFFFF/3), 1*(0xFFFFFF/3), 0};
    //const uint32_t colors[4] = {0xFFFFFF, 0x1E1611*8, 0x100E13*8, 0};
    const uint32_t width = bytes_per_tile*tiles_per_row;
    const int32_t height = bytes_per_tile*tiles_per_column;
    toBmp_bitIndexed(out, 2*BUFFER_SIZE, final_buffer, bits_per_pixel, width, -height, colors);

    return 0;
}
