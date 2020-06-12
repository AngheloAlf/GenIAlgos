#pragma once
#ifndef POINTERS_PKSPECIESSTATS_PKSTATSBYDEX_H
#define POINTERS_PKSPECIESSTATS_PKSTATSBYDEX_H

#include <stddef.h>
#include <stdint.h>


#define PKSTSBYID_STATS_BASE_ENTRY  0x383C2
#define PKSTSBYID_STATS_ENTRY_LEN   0x1C


typedef struct{
    uint8_t hp;
    uint8_t attack;
    uint8_t defense;
    uint8_t speed;
    uint8_t special;
} PkStats_t;

typedef struct{
    uint8_t dimFrontSprite;
    uint16_t frontSpritePtr;
    uint16_t backSpritePtr;
} SpritePicturePtrs_t;

typedef struct{
    uint8_t move0;
    uint8_t move1;
    uint8_t move2;
    uint8_t move3;
} PkKnownMoves_t;

typedef struct{
    uint8_t flag0;
    uint8_t flag1;
    uint8_t flag2;
    uint8_t flag3;
    uint8_t flag4;
    uint8_t flag5;
    uint8_t flag6;
    uint8_t flag7;
} TmHmFlags_t;

typedef struct{
    uint8_t dexId;
    PkStats_t baseStats;
    uint8_t type1;
    uint8_t type2;
    uint8_t catchRate;
    uint8_t baseExpYield;
    SpritePicturePtrs_t spritePtrs;
    PkKnownMoves_t lvl1Moves;
    uint8_t growthRate;
    TmHmFlags_t tmHmFlags;
} PkSpeciesStats_t;


size_t calculate_pk_stat_entry_offset(size_t dex_number);
void load_pk_stats_by_dex_to_arr(uint8_t *dst_arr, const uint8_t *src_data, int64_t src_data_offset, size_t pkDex);
void load_pk_stats_by_dex_to_struct(PkSpeciesStats_t *dst_stru, const uint8_t *src_data, int64_t src_data_offset, size_t pkDex);


#endif /* POINTERS_PKSPECIESSTATS_PKSTATSBYDEX_H */
