#pragma once
#ifndef COMMON_BITOPERATIONS_H
#define COMMON_BITOPERATIONS_H

#include "common/externalHeaders/externalHeaders.h"

uint8_t RLC(uint8_t number);
uint8_t RRC(uint8_t number);

uint8_t SWAP(uint8_t number);

uint8_t BIT(uint8_t number, uint8_t bit_i);

#endif /* COMMON_BITOPERATIONS_H */
