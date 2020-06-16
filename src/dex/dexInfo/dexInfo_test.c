#include "dexInfo.h"

#include "utils/io/io.h"
#include "utils/numbers/numbers.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


#define UNDERLINE(_text) "\e[4m"_text"\e[0m"

void check_arguments(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s %s %s\n", argv[0], UNDERLINE("romfile"), UNDERLINE("internal_id"));
        exit(-1);
    }
}


int main(int argc, char **argv){
    check_arguments(argc, argv);
    const char *filename = argv[1];
    uint8_t internal_id = strToNumber(argv[2]);

    // printf("Reading: %s\n", filename);
    size_t file_size = getFileSize(filename);
    uint8_t *data = malloc(file_size*sizeof(uint8_t));
    readFile(data, file_size, filename, 0);

    uint8_t bank;
    uint16_t ptr = getDexInfosPtrById(&bank, data, 0, internal_id);
    printf("internal_id: 0x%02"PRIX8"\n", internal_id);
    printf("\tbank: 0x%02"PRIX8"\n\tptr:  0x%04"PRIX16"\n", bank, ptr);

    printf("\n");

    DexInfos_t pkDexInfo;
    getDexInfoById_toStruct(&pkDexInfo, data, 0, internal_id);

    printf("feet:         %03"PRIu8"\n",  pkDexInfo.feet);
    printf("inches:       %03"PRIu8"\n",  pkDexInfo.inches);
    printf("weight:       %03"PRIu16"\n", pkDexInfo.weight);
    printf("always0x17:   0x%02"PRIX8"\n",  pkDexInfo.always0x17);
    printf("dexEntryPtr:  0x%04"PRIX16"\n", pkDexInfo.dexEntryPtr);
    printf("dexEntryBank: 0x%02"PRIX8"\n",  pkDexInfo.dexEntryBank);
    printf("endOfData:    0x%02"PRIX8"\n",  pkDexInfo.endOfData);

    size_t entries_len = getEntriesLenById(data, 0, internal_id);
    uint8_t *entries = malloc(entries_len*sizeof(uint8_t));
    size_t first_entry_len;
    printf("len: %zu\n", entries_len);
    getEntriesById_toArr(&first_entry_len, entries, data, 0, internal_id);
    printf("entries:\n");
    for(size_t i = 0; i < entries_len; ++i){
        printf("\t%02zu: 0x%02"PRIX8"\n", i, entries[i]);
    }

    free(entries);
    free(data);
    return 0;
}
