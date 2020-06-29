#include "io.h"

#include "utils/numbers/numbers.h"
#include "utils/text/text.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void check_arguments(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s %s %s\n", argv[0], UNDERLINE("file"), UNDERLINE("bank_size"));
        exit(-1);
    }
}

void split_into_banks(const char *filename, size_t bank_size){
    int64_t file_size = getFileSize(filename);
    uint8_t *data = malloc(file_size*sizeof(uint8_t));
    readFile(data, file_size, filename, 0);

    printf("full size: %zu\n", file_size);

    size_t new_name_len = strlen(filename) + 128;
    char *new_name = malloc(new_name_len * sizeof(char));

    size_t i = 0;
    while((file_size -= bank_size) >= 0){
        int retval = snprintf(new_name, new_name_len, "%s.0x%02"PRIX64".bank", filename, i);
        assert(retval > 0);

        printf("%s %zu\n", new_name, i*bank_size);
        writeFile(&data[i*bank_size], bank_size, new_name, 0);

        ++i;
    }

    free(new_name);
    free(data);
}

void check_arguments2(int argc, char **argv){
    if(argc < 4){
        printf("Usage: %s %s %s %s\n", argv[0], UNDERLINE("file"), UNDERLINE("value"), UNDERLINE("out name"));
        exit(-1);
    }
}

void substract_to_each_byte(const char *filename, uint8_t value, const char *out){
    size_t file_size = getFileSize(filename);
    uint8_t *data = malloc(file_size*sizeof(uint8_t));
    readFile(data, file_size, filename, 0);

    for(size_t i = 0; i < file_size; ++i){
        data[i] -= value;
    }

    writeFile(data, file_size, out, 0);

    free(data);
}

int main(int argc, char **argv){
    // check_arguments(argc, argv);
    // split_into_banks(argv[1], strToNumber(argv[2]));

    check_arguments2(argc, argv);
    substract_to_each_byte(argv[1], strToNumber(argv[2]), argv[3]);

    return 0;
}

