#pragma once
#ifndef TEXT_TOASCII_H
#define TEXT_TOASCII_H

#include "common/externalHeaders/externalHeaders.h"

#define TEXT_END        0x50

const char *charAsAsciiStr(uint8_t character);
size_t text_lenAsAscii(size_t size, uint8_t buffer[size]);
void text_toAsciiStr(char *dst_buff, size_t src_size, const uint8_t src_buff[src_size]);

#endif /* TEXT_TOASCII_H */
