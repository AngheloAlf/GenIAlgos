#pragma once
#ifndef PK_NAMES_H
#define PK_NAMES_H

#include "common/externalHeaders/externalHeaders.h"

#define PKNAMES_BANK                0x07
#define PKNAMES_PTR_TO_NAMES_LOW    0x2FAE
#define PKNAMES_PTR_TO_NAMES_HIGH   0x2FAF

#define PKNAMES_NAME_LEN            0x0A

void pkNames_getNameById(uint8_t dst_buff[PKNAMES_NAME_LEN], const uint8_t *src_data, int64_t src_data_offset, uint8_t pk_id);

#endif /* PK_NAMES_H */
