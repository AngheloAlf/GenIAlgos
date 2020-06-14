#include "dexNumbers.h"

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

    size_t file_size = get_file_size(filename);
    uint8_t *data = malloc(file_size*sizeof(uint8_t));
    read_file(filename, file_size, data);

    dex_num = dexNumById(data, 0, internal_id);
    printf("internal_id: 0x%02"PRIX8"\n\tdex_num: %03"PRIu8"\n", internal_id, dex_num);

    free(data);
    return 0;
}
