#include "bitplanes.h"

#include "utils/io/io.h"
#include "utils/text/text.h"

#include <stdlib.h>

void check_arguments(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s %s %s\n", argv[0], UNDERLINE("sprite_file"), UNDERLINE("out_name"));
        exit(-1);
    }
}

int main(int argc, char **argv){
    check_arguments(argc, argv);
    const char *filename = argv[1];

    size_t size = getFileSize(filename);
    uint8_t *sprite = malloc(size*sizeof(uint8_t));

    readFile(sprite, size, filename, 0);

    mergeBitplanes(size, sprite);

    const char *out = argv[2];
    writeFile(sprite, size, out, 0);

    free(sprite);
    return 0;
}
