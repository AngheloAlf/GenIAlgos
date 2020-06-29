#include "toAscii.h"

#include <string.h>

void text_toAsciiStr(char *dst_buff, size_t src_size, const uint8_t src_buff[src_size]){
    size_t dst_i = 0;
    for(size_t i = 0; i < src_size; ++i){
        if(src_buff[i] == TEXT_END){
            break;
        }
        const char *chr = charAsAsciiStr(src_buff[i]);
        size_t chr_len = strlen(chr);
        strncpy(&dst_buff[dst_i], chr, chr_len);
        dst_i += chr_len;
    }
    dst_buff[dst_i] = 0;
}
