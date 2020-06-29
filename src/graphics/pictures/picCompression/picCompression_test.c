#include "picCompression.h"

#include "utils/io/io.h"
#include "utils/text/text.h"

#include <stdlib.h>
#include <assert.h>

#define BUFFER_SIZE             0x188

void check_arguments(int argc, char **argv){
    if(argc < 2){
        printf("Usage: %s %s\n", argv[0], UNDERLINE("compressed_sprite_file"));
        exit(-1);
    }
}

int main(int argc, char **argv){
    check_arguments(argc, argv);

    const char *filename = argv[1];

    size_t size = getFileSize(filename);
    uint8_t *compressed = calloc(size, sizeof(uint8_t));
    readFile(compressed, size, filename, 0);

    uint8_t buffer[2*BUFFER_SIZE];
    decompressPicture(BUFFER_SIZE, buffer, &buffer[BUFFER_SIZE], compressed);

    writeFile(buffer, 2*BUFFER_SIZE, "buffer_dump.bin", 0);

    free(compressed);
    return 0;
}
