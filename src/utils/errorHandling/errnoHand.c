#include "errorHandling.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>


noreturn void showErrnoAndHalt(){
    fprintf(stderr, "%s\n", strerror(errno));
    assert(!errno);
    exit(errno);
}
