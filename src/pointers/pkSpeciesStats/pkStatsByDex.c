#include "pkStatsByDex.h"


size_t calculate_pk_stat_entry_offset(size_t dex_number){
    return dex_number*PKSTSBYID_STATS_ENTRY_LEN;
}

void load_pk_stats_by_dex_to_arr(uint8_t *dst_arr, const uint8_t *src_data, int64_t src_data_offset, size_t pkDex){
    size_t entry_offset = calculate_pk_stat_entry_offset(pkDex);
    for(size_t i = 0; i < PKSTSBYID_STATS_ENTRY_LEN; ++i){
        dst_arr[i] = src_data[PKSTSBYID_STATS_BASE_ENTRY + entry_offset + src_data_offset + i];
    }
}

void load_pk_stats_by_dex_to_struct(PkSpeciesStats_t *dst_stru, const uint8_t *src_data, int64_t src_data_offset, size_t pkDex){
    uint8_t aux_arr[PKSTSBYID_STATS_ENTRY_LEN];
    load_pk_stats_by_dex_to_arr(aux_arr, src_data, src_data_offset, pkDex);

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
    dst_stru->spritePtrs.frontSpritePtr = (aux_arr[0x0B]<<8) | aux_arr[0x0C];
    dst_stru->spritePtrs.backSpritePtr  = (aux_arr[0x0D]<<8) | aux_arr[0x0E];

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
