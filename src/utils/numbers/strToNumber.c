#include "numbers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>


uintmax_t strToNumber(const char *str_val){
    if(isdigit(str_val[0]) == 0){
        fprintf(stderr, "Expected a numerical secuence, not '%s'\n", str_val);
        assert(isdigit(str_val[0]) != 0);
        exit(-1);
    }
    errno = 0;
    char *endptr;
    uintmax_t num_val = strtoumax(str_val, &endptr, 10);
    if(errno){
        fprintf(stderr, "%s\n", strerror(errno));
        assert(!errno);
        exit(errno);
    }
    return num_val;
}
