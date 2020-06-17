#include "io.h"

#include "utils/errorHandling/errorHandling.h"

#include <assert.h>


size_t getFileSize(const char *filename){
    int retval;

    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){
        showErrnoAndHalt();
    }

    retval = fseek(fp, 0L, SEEK_END);
    if(retval != 0){
        showErrnoAndHalt();
    }

    long sz = ftell(fp);
    if(sz < 0){
        showErrnoAndHalt();
    }

    retval = fclose(fp);
    if(retval != 0){
        showErrnoAndHalt();
    }

    return sz;
}

size_t fgetFileSize(FILE *fp){
    fpos_t pos;
    int retval;

    retval = fgetpos(fp, &pos);
    if(retval != 0){
        showErrnoAndHalt();
    }

    retval = fseek(fp, 0L, SEEK_END);
    if(retval != 0){
        showErrnoAndHalt();
    }

    long sz = ftell(fp);
    if(sz < 0){
        showErrnoAndHalt();
    }

    retval = fsetpos(fp, &pos);
    if(retval != 0){
        showErrnoAndHalt();
    }

    return sz;
}
