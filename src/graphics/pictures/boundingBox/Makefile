MODULE_NAME  = boundingBox
SOURCE_FILES = addBoundingBox.c

all: module

module: $(MODULE_NAME).h $(SOURCE_FILES)
	gcc -std=c11 -Wall -Wextra -g -fno-common -o $(MODULE_NAME).o -c $(SOURCE_FILES)

module_test: module $(MODULE_NAME)_test.c
	@echo 
	gcc -std=c11 -Wall -Wextra -g -fno-common -o $(MODULE_NAME).elf $(MODULE_NAME).o $(MODULE_NAME)_test.c


clean:
	rm *.o *.elf
