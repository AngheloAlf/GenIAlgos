#include "io.h"

#include "utils/errorHandling/errorHandling.h"

#include <assert.h>

void readFile(uint8_t *dst_buff, size_t bytes_to_read, const char *filename, size_t file_offset){
    int retval;

    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){
        showErrnoAndHalt();
    }

    retval = fseek(fp, file_offset, SEEK_SET);
    if(retval != 0){
        showErrnoAndHalt();
    }

    size_t items_read = fread(dst_buff, 1, bytes_to_read, fp);
    assert(items_read == bytes_to_read);

    retval = fclose(fp);
    if(retval != 0){
        showErrnoAndHalt();
    }
}
