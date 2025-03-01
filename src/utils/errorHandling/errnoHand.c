#include "errorHandling.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


noreturn void showErrnoAndHalt(){
    fprintf(stderr, "errno %i: %s\n", errno, strerror(errno));
    printBacktrace();
    exit(errno);
}
