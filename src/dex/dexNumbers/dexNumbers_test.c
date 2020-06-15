#include "dexNumbers.h"

#include "utils/io/io.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <string.h>


#define UNDERLINE(_text) "\e[4m"_text"\e[0m"

void check_arguments(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s %s %s\n", argv[0], UNDERLINE("romfile"), UNDERLINE("internal_id"));
        exit(-1);
    }
}

uintmax_t str_to_number(const char *str_val){
    errno = 0;
    char *endptr;
    uintmax_t num_val = strtoumax(str_val, &endptr, 10);
    if(errno){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(errno);
    }
    return num_val;
}


int main(int argc, char **argv){
    check_arguments(argc, argv);
    const char *filename = argv[1];
    uint8_t internal_id = str_to_number(argv[2]);
    uint8_t dex_num;

    size_t file_size = getFileSize(filename);
    uint8_t *data = malloc(file_size*sizeof(uint8_t));
    readFile(data, file_size, filename, 0);

    dex_num = dexNumById(data, 0, internal_id);
    printf("internal_id: 0x%02"PRIX8"\n\tdex_num: %03"PRIu8"\n", internal_id, dex_num);

    free(data);
    return 0;
}
