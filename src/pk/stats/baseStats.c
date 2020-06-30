#include "stats.h"

#include "common/ptrs/ptrs.h"

uint32_t pkStats_ptr(const uint8_t *srcbuff, uint8_t dex_number){
    uint8_t bank;
    uint16_t ptr;
    if(dex_number == 151){
        bank = srcbuff[PKSTATS_PTR_TO_BANKNO_151];
        ptr = ptrs_fetch16(srcbuff, PKSTATS_PTR_TO_STATSPTR_151_HIGH, PKSTATS_PTR_TO_STATSPTR_151_LOW);
        return absolutePtr(bank, ptr);
    }
    --dex_number;
    bank = srcbuff[PKSTATS_PTR_TO_BANKNO];
    ptr = ptrs_fetch16(srcbuff, PKSTATS_PTR_TO_STATSPTR_HIGH, PKSTATS_PTR_TO_STATSPTR_LOW);
    return absolutePtr(bank, ptr) + dex_number*PKSTATS_STATS_ENTRY_LEN;
}

void pkStats_byPtrToArr(uint8_t *dstbuff, const uint8_t *srcbuff, uint32_t ptr){
    for(size_t i = 0; i < PKSTATS_STATS_ENTRY_LEN; ++i){
        dstbuff[i] = srcbuff[ptr + i];
    }
}

void pkStats_byDexToArr(uint8_t *dstbuff, const uint8_t *srcbuff, uint8_t dex_number){
    uint32_t ptr = pkStats_ptr(srcbuff, dex_number);
    pkStats_byPtrToArr(dstbuff, srcbuff, ptr);
}

void pkStats_byDexToStruct(PkSpeciesStats_t *dst_stru, const uint8_t *src_data, uint8_t dex_number){
    uint8_t aux_arr[PKSTATS_STATS_ENTRY_LEN];
    pkStats_byDexToArr(aux_arr, src_data, dex_number);

    dst_stru->dexId = aux_arr[0x00];

    dst_stru->baseStats.hp      = aux_arr[0x01];
    dst_stru->baseStats.attack  = aux_arr[0x02];
    dst_stru->baseStats.defense = aux_arr[0x03];
    dst_stru->baseStats.speed   = aux_arr[0x04];
    dst_stru->baseStats.special = aux_arr[0x05];

    dst_stru->type1         = aux_arr[0x06];
    dst_stru->type2         = aux_arr[0x07];
    dst_stru->catchRate     = aux_arr[0x08];
    dst_stru->baseExpYield  = aux_arr[0x09];

    dst_stru->spritePtrs.dimFrontSprite =  aux_arr[0x0A];
    dst_stru->spritePtrs.frontSpritePtr = (aux_arr[0x0C]<<8) | aux_arr[0x0B];
    dst_stru->spritePtrs.backSpritePtr  = (aux_arr[0x0E]<<8) | aux_arr[0x0D];

    dst_stru->lvl1Moves.move0 = aux_arr[0x0F];
    dst_stru->lvl1Moves.move1 = aux_arr[0x10];
    dst_stru->lvl1Moves.move2 = aux_arr[0x11];
    dst_stru->lvl1Moves.move3 = aux_arr[0x12];

    dst_stru->growthRate = aux_arr[0x13];

    dst_stru->tmHmFlags.flag0 = aux_arr[0x14];
    dst_stru->tmHmFlags.flag1 = aux_arr[0x15];
    dst_stru->tmHmFlags.flag2 = aux_arr[0x16];
    dst_stru->tmHmFlags.flag3 = aux_arr[0x17];
    dst_stru->tmHmFlags.flag4 = aux_arr[0x18];
    dst_stru->tmHmFlags.flag5 = aux_arr[0x19];
    dst_stru->tmHmFlags.flag6 = aux_arr[0x1A];
    dst_stru->tmHmFlags.flag7 = aux_arr[0x1B];
}
