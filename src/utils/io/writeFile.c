#include "io.h"

#include "utils/errorHandling/errorHandling.h"

#include <assert.h>

void writeFile(uint8_t *src_buff, size_t bytes_to_write, const char *filename, size_t file_offset){
    int retval;

    FILE *fp = fopen(filename, "wb");
    if(fp == NULL){
        showErrnoAndHalt();
    }

    retval = fseek(fp, file_offset, SEEK_SET);
    if(retval != 0){
        showErrnoAndHalt();
    }

    size_t items_writed = fwrite(src_buff, 1, bytes_to_write, fp);
    assert(items_writed == bytes_to_write);

    retval = fclose(fp);
    if(retval != 0){
        showErrnoAndHalt();
    }
}
