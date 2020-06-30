MODULE_NAME  = stats
SOURCE_FILES = baseStats.c

LIBS            = -lptrs
LIBS_PATHS      = -L. -L../../common/ptrs/
INCLUDE_PATHS   = -I../../

TEST_LIBS           = -lio -lnumbers -lerrorHandling
TEST_LIBS_PATHS     = -L../../utils/io/ -L../../utils/numbers/ -L../../utils/errorHandling/
TEST_INCLUDE_PATHS  = 

STD         = -std=c11
WARNINGS    = -Wall -Wextra -Wunused-macros -Wendif-labels
C_FLAGS     = -fno-common -fPIC -rdynamic
DEBUG       = -g
OPTIMIZA    = -Og

all: module

module: $(MODULE_NAME).h $(SOURCE_FILES)
	rm -f lib$(MODULE_NAME).a *.o
	gcc -c $(SOURCE_FILES) $(STD) $(WARNINGS) $(C_FLAGS) $(INCLUDE_PATHS) $(LIBS_PATHS) $(LIBS) $(DEBUG) $(OPTIMIZA)
	ar -rcs lib$(MODULE_NAME).a *.o

module_test: module $(MODULE_NAME)_test.c
	@echo 
	gcc -o $(MODULE_NAME).elf $(MODULE_NAME)_test.c -l$(MODULE_NAME) $(STD) $(WARNINGS) $(C_FLAGS) $(TEST_INCLUDE_PATHS) $(INCLUDE_PATHS) $(TEST_LIBS_PATHS) $(LIBS_PATHS) $(TEST_LIBS) $(LIBS) $(DEBUG) $(OPTIMIZA)

test_module: module_test

clean:
	rm -f *.o *.a *.elf
