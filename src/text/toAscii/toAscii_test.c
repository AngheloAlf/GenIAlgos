#include "toAscii.h"

#include "dex/dexInfo/dexInfo.h"

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

    printf("internal_id: 0x%02"PRIX8"\n", internal_id);

    size_t specie_len = getSpiciesNameLenById(data, 0, internal_id);
    uint8_t *specie_name = malloc(specie_len*sizeof(uint8_t));
    getSpeciesNameById(specie_name, data, 0, internal_id);
    for(size_t i = 0; i < specie_len; ++i){
        printf("%s", charAsAsciiStr(specie_name[i]));
    }
    printf("\n");
    free(specie_name);

    size_t entries_len = getEntriesLenById(data, 0, internal_id);
    uint8_t *entries = malloc(entries_len*sizeof(uint8_t));
    size_t first_entry_len;
    getEntriesById_toArr(&first_entry_len, entries, data, 0, internal_id);
    printf("\ndex entry:\n");
    //printf("first entry:\n\n");
    for(size_t i = 0; i < first_entry_len; ++i){
        printf("%s", charAsAsciiStr(entries[i]));
        /*if(strcmp(charAsAsciiStr(entries[i]), "(nil)") == 0){
            printf("(0x%02"PRIX8")", entries[i]);
        }*/
    }
    //printf("\n\nsecond entry:\n\n");
    for(size_t i = first_entry_len; i < entries_len; ++i){
        printf("%s", charAsAsciiStr(entries[i]));
        /*if(strcmp(charAsAsciiStr(entries[i]), "(nil)") == 0){
            printf("(0x%02"PRIX8")", entries[i]);
        }*/
    }
    printf("\n");
    free(entries);

    free(data);
    return 0;
}
