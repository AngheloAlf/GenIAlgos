#include "pkStatsByDex.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <string.h>


#define UNDERLINE(_text) "\e[4m"_text"\e[0m"

void check_arguments(int argc, char **argv){
    if(argc < 2){
        printf("Usage: %s %s\n", argv[0], UNDERLINE("sprite_file"));
        exit(-1);
    }
}

size_t get_file_size(const char *filename){
    int retval;

    FILE *fp = fopen(filename, "rb");
    assert(fp != NULL);

    retval = fseek(fp, 0L, SEEK_END);
    assert(retval >= 0);

    long sz = ftell(fp);
    assert(sz >= 0);

    retval = fclose(fp);
    assert(retval >= 0);

    return sz;
}

size_t fget_file_size(FILE *fp){
    fpos_t pos;
    int retval;

    retval = fgetpos(fp, &pos);
    assert(retval >= 0);

    retval = fseek(fp, 0L, SEEK_END);
    assert(retval >= 0);

    long sz = ftell(fp);
    assert(sz >= 0);

    retval = fsetpos(fp, &pos);
    assert(retval >= 0);

    return sz;
}

void read_file(const char *filename, size_t bytes_to_read, uint8_t *dst_buff){
    int retval;

    FILE *fp = fopen(filename, "rb");
    assert(fp != NULL);

    size_t items_read = fread(dst_buff, 1, bytes_to_read, fp);
    assert(items_read == bytes_to_read);

    retval = fclose(fp);
    assert(retval >= 0);
}


int main(int argc, char **argv){
    check_arguments(argc, argv);
    const char *filename = argv[1];
    uintmax_t dex_num;

    errno = 0;
    char *endptr;
    dex_num = strtoumax(argv[2], &endptr, 10);
    if(errno){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(-1);
    }

    size_t file_size = get_file_size(filename);
    uint8_t *data = malloc(file_size*sizeof(uint8_t));
    read_file(filename, file_size, data);

    PkSpeciesStats_t stats_entry;
    load_pk_stats_by_dex_to_struct(&stats_entry, data, 0, dex_num);

    free(data);

    printf("%ld\n", dex_num);

    printf("dexId: %03"PRIu8"\n", stats_entry.dexId);

    printf("\n");
    printf("baseHp:      0x%02"PRIX8"\n", stats_entry.baseStats.hp);
    printf("baseAttack:  0x%02"PRIX8"\n", stats_entry.baseStats.attack);
    printf("baseDefense: 0x%02"PRIX8"\n", stats_entry.baseStats.defense);
    printf("baseSpeed:   0x%02"PRIX8"\n", stats_entry.baseStats.speed);
    printf("baseSpecial: 0x%02"PRIX8"\n", stats_entry.baseStats.special);

    printf("\n");
    printf("type1:        0x%02"PRIX8"\n", stats_entry.type1);
    printf("type2:        0x%02"PRIX8"\n", stats_entry.type2);
    printf("catchRate:    0x%02"PRIX8"\n", stats_entry.catchRate);
    printf("baseExpYield: 0x%02"PRIX8"\n", stats_entry.baseExpYield);

    printf("\n");
    printf("dimFrontSprite: 0x%02"PRIX8"\n", stats_entry.spritePtrs.dimFrontSprite);
    printf("frontSpritePtr: 0x%04"PRIX16"\n", stats_entry.spritePtrs.frontSpritePtr);
    printf("backSpritePtr:  0x%04"PRIX16"\n", stats_entry.spritePtrs.backSpritePtr);

    printf("\n");
    printf("lvl1Move0: 0x%02"PRIX8"\n", stats_entry.lvl1Moves.move0);
    printf("lvl1Move1: 0x%02"PRIX8"\n", stats_entry.lvl1Moves.move1);
    printf("lvl1Move2: 0x%02"PRIX8"\n", stats_entry.lvl1Moves.move2);
    printf("lvl1Move3: 0x%02"PRIX8"\n", stats_entry.lvl1Moves.move3);

    printf("\n");
    printf("growthRate: 0x%02"PRIX8"\n", stats_entry.growthRate);

    printf("\n");
    printf("tmHmFlag0: 0x%02"PRIX8"\n", stats_entry.tmHmFlags.flag0);
    printf("tmHmFlag1: 0x%02"PRIX8"\n", stats_entry.tmHmFlags.flag1);
    printf("tmHmFlag2: 0x%02"PRIX8"\n", stats_entry.tmHmFlags.flag2);
    printf("tmHmFlag3: 0x%02"PRIX8"\n", stats_entry.tmHmFlags.flag3);
    printf("tmHmFlag4: 0x%02"PRIX8"\n", stats_entry.tmHmFlags.flag4);
    printf("tmHmFlag5: 0x%02"PRIX8"\n", stats_entry.tmHmFlags.flag5);
    printf("tmHmFlag6: 0x%02"PRIX8"\n", stats_entry.tmHmFlags.flag6);
    printf("tmHmFlag7: 0x%02"PRIX8"\n", stats_entry.tmHmFlags.flag7);

    return 0;
}
