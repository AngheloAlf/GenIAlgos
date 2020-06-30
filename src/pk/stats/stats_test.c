#include "stats.h"

#include "utils/io/io.h"
#include "utils/numbers/numbers.h"
#include "utils/text/text.h"

#include <stdio.h>
#include <stdlib.h>

void check_arguments(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s %s %s\n", argv[0], UNDERLINE("romfile"), UNDERLINE("dex_number"));
        exit(-1);
    }
}

void show_pk_stats(const PkSpeciesStats_t *entry){
    printf("dexId: %03"PRIu8"\n", entry->dexId);

    printf("\n");
    printf("baseHp:      0x%02"PRIX8"\n", entry->baseStats.hp);
    printf("baseAttack:  0x%02"PRIX8"\n", entry->baseStats.attack);
    printf("baseDefense: 0x%02"PRIX8"\n", entry->baseStats.defense);
    printf("baseSpeed:   0x%02"PRIX8"\n", entry->baseStats.speed);
    printf("baseSpecial: 0x%02"PRIX8"\n", entry->baseStats.special);

    printf("\n");
    printf("type1:        0x%02"PRIX8"\n", entry->type1);
    printf("type2:        0x%02"PRIX8"\n", entry->type2);
    printf("catchRate:    0x%02"PRIX8"\n", entry->catchRate);
    printf("baseExpYield: 0x%02"PRIX8"\n", entry->baseExpYield);

    printf("\n");
    printf("dimFrontSprite: 0x%02"PRIX8"\n", entry->spritePtrs.dimFrontSprite);
    printf("frontSpritePtr: 0x%04"PRIX16"\n", entry->spritePtrs.frontSpritePtr);
    printf("backSpritePtr:  0x%04"PRIX16"\n", entry->spritePtrs.backSpritePtr);

    printf("\n");
    printf("lvl1Move0: 0x%02"PRIX8"\n", entry->lvl1Moves.move0);
    printf("lvl1Move1: 0x%02"PRIX8"\n", entry->lvl1Moves.move1);
    printf("lvl1Move2: 0x%02"PRIX8"\n", entry->lvl1Moves.move2);
    printf("lvl1Move3: 0x%02"PRIX8"\n", entry->lvl1Moves.move3);

    printf("\n");
    printf("growthRate: 0x%02"PRIX8"\n", entry->growthRate);

    printf("\n");
    printf("tmHmFlag0: 0x%02"PRIX8"\n", entry->tmHmFlags.flag0);
    printf("tmHmFlag1: 0x%02"PRIX8"\n", entry->tmHmFlags.flag1);
    printf("tmHmFlag2: 0x%02"PRIX8"\n", entry->tmHmFlags.flag2);
    printf("tmHmFlag3: 0x%02"PRIX8"\n", entry->tmHmFlags.flag3);
    printf("tmHmFlag4: 0x%02"PRIX8"\n", entry->tmHmFlags.flag4);
    printf("tmHmFlag5: 0x%02"PRIX8"\n", entry->tmHmFlags.flag5);
    printf("tmHmFlag6: 0x%02"PRIX8"\n", entry->tmHmFlags.flag6);
    printf("tmHmFlag7: 0x%02"PRIX8"\n", entry->tmHmFlags.flag7);
}


int main(int argc, char **argv){
    check_arguments(argc, argv);
    const char *filename = argv[1];
    uint8_t dex_num = strToNumber(argv[2]);

    size_t file_size = getFileSize(filename);
    uint8_t *data = malloc(file_size*sizeof(uint8_t));
    readFile(data, file_size, filename, 0);

    PkSpeciesStats_t stats_entry;
    pkStats_byDexToStruct(&stats_entry, data, dex_num, false);

    printf("\n%03"PRIu8"\n", dex_num);
    printf("entry_pos:    0x%08"PRIX32"\n", pkStats_ptr(data, dex_num, false));
    show_pk_stats(&stats_entry);

    free(data);
    return 0;
}
