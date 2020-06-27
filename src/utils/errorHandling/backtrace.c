#include "errorHandling.h"

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define BT_BUF_SIZE 100

void printBacktrace(){
    void *buffer[BT_BUF_SIZE];
    int nptrs = backtrace(buffer, BT_BUF_SIZE);

    fprintf(stderr, "\nbacktrace:\n");
    backtrace_symbols_fd(buffer, nptrs, STDERR_FILENO);

    fprintf(stderr, "\n");
}
