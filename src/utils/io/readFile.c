#include "io.h"

#include <assert.h>
#include <errno.h>
#include <string.h>


void readFile(uint8_t *dst_buff, size_t bytes_to_read, const char *filename, size_t file_offset){
    int retval;

    errno = 0;
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        // exit(errno);
    }
    assert(fp != NULL);

    retval = fseek(fp, file_offset, SEEK_SET);
    assert(retval == 0);

    size_t items_read = fread(dst_buff, 1, bytes_to_read, fp);
    assert(items_read == bytes_to_read);

    retval = fclose(fp);
    assert(retval >= 0);
}
