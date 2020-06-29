#include "toAscii.h"

#include <string.h>

size_t text_lenAsAscii(size_t size, uint8_t buffer[size]){
    size_t len = 0;
    for(size_t i = 0; i < size; ++i){
        if(buffer[i] == TEXT_END){
            return len;
        }
        len += strlen(charAsAsciiStr(buffer[i]));
    }
    return len;
}
