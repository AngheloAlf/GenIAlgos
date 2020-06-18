#pragma once
#ifndef UTILS_IO_H
#define UTILS_IO_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


size_t getFileSize(const char *filename);
size_t fgetFileSize(FILE *fp);

void readFile(uint8_t *dst_buff, size_t bytes_to_read, const char *filename, size_t file_offset);
void writeFile(uint8_t *src_buff, size_t bytes_to_write, const char *filename, size_t file_offset);

#endif /* UTILS_IO_H */
