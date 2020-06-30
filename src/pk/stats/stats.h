#pragma once
#ifndef PK_STATS_H
#define PK_STATS_H

#include "common/externalHeaders/externalHeaders.h"

#define PKSTATS_PTR_TO_BANKNO               0x153B
#define PKSTATS_PTR_TO_STATSPTR_LOW         0x1578
#define PKSTATS_PTR_TO_STATSPTR_HIGH        0x1579

#define PKSTATS_PTR_TO_BANKNO_151           0x159C
#define PKSTATS_PTR_TO_STATSPTR_151_LOW     0x1593
#define PKSTATS_PTR_TO_STATSPTR_151_HIGH    0x1594

#define PKSTATS_STATS_ENTRY_LEN   0x1C

typedef enum{
    PkType_Normal = 0x00,
    PkType_Fighting = 0x01,
    PkType_Flying = 0x02,
    PkType_Poison = 0x03,
    PkType_Ground = 0x04,
    PkType_Rock = 0x05,
    PkType_Bird = 0x06,
    PkType_Bug = 0x07,
    PkType_Ghost = 0x08,
    /*PkType_unused00 = 0x09,
    PkType_unused01 = 0x0A,
    PkType_unused02 = 0x0B,
    PkType_unused03 = 0x0C,
    PkType_unused04 = 0x0D,
    PkType_unused05 = 0x0E,
    PkType_unused06 = 0x0F,
    PkType_unused07 = 0x10,
    PkType_unused08 = 0x11,
    PkType_unused09 = 0x12,
    PkType_unused10 = 0x13,*/
    PkType_Fire = 0x14,
    PkType_Water = 0x15,
    PkType_Grass = 0x16,
    PkType_Electric = 0x17,
    PkType_Psychic = 0x18,
    PkType_Ice = 0x19,
    PkType_Dragon = 0x1A
} PkTypes_e;


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


uint32_t pkStats_ptr(const uint8_t *srcbuff, uint8_t dex_number);

void pkStats_byPtrToArr(uint8_t *dstbuff, const uint8_t *srcbuff, uint32_t ptr);
void pkStats_byDexToArr(uint8_t *dstbuff, const uint8_t *srcbuff, uint8_t dex_number);
void pkStats_byDexToStruct(PkSpeciesStats_t *dst_stru, const uint8_t *src_data, uint8_t dex_number);

#endif /* PK_STATS_H */
