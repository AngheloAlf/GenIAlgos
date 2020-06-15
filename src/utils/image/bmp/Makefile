MODULE_NAME     = bmp
SOURCE_FILES    = toBmp.c

LIBS            = 
LIBS_PATHS      = -L.
INCLUDE_PATHS   = 

STD         = -std=c11
WARNINGS    = -Wall -Wextra
C_FLAGS     = -fno-common -fPIC
DEBUG       = -g
OPTIMIZA    = -Og


all: module

module: $(MODULE_NAME).h $(SOURCE_FILES)
	gcc -c $(SOURCE_FILES) $(STD) $(WARNINGS) $(C_FLAGS) $(INCLUDE_PATHS) $(LIBS_PATHS) $(LIBS) $(DEBUG) $(OPTIMIZA)
	ar -rcs lib$(MODULE_NAME).a *.o

module_test: module $(MODULE_NAME)_test.c
	@echo 
	gcc -o $(MODULE_NAME).elf $(MODULE_NAME)_test.c -l$(MODULE_NAME) $(STD) $(WARNINGS) $(C_FLAGS) $(INCLUDE_PATHS) $(LIBS_PATHS) $(LIBS) $(DEBUG) $(OPTIMIZA)

test_module: module_test


clean:
	rm -f *.o *.elf
