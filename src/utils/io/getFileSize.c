#include "io.h"

#include <assert.h>


size_t getFileSize(const char *filename){
    int retval;

    FILE *fp = fopen(filename, "rb");
    assert(fp != NULL);

    retval = fseek(fp, 0L, SEEK_END);
    assert(retval == 0);

    long sz = ftell(fp);
    assert(sz >= 0);

    retval = fclose(fp);
    assert(retval == 0);

    return sz;
}

size_t fgetFileSize(FILE *fp){
    fpos_t pos;
    int retval;

    retval = fgetpos(fp, &pos);
    assert(retval == 0);

    retval = fseek(fp, 0L, SEEK_END);
    assert(retval == 0);

    long sz = ftell(fp);
    assert(sz >= 0);

    retval = fsetpos(fp, &pos);
    assert(retval == 0);

    return sz;
}
