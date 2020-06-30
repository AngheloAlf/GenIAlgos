MODULE_NAME  = pkPicExtractor
SOURCE_FILES = pkPicExtractor.c

LIBS            = -lio -lnumbers -lbmp -lerrorHandling -ldexNumbers -lnames -ltoAscii -lstats -lbankSwitch -ldexInfo -lpicCompression -lboundingBox -lbitplanes -lpixelOrder -lptrs
LIBS_PATHS      = -L. -L../../src/utils/io/ -L../../src/utils/numbers/ -L../../src/utils/image/bmp/ -L../../src/utils/errorHandling/ -L../../src/dex/dexNumbers/ -L../../src/pk/names/ -L../../src/text/toAscii/ -L../../src/pk/stats/ -L../../src/graphics/pictures/bankSwitch/ -L../../src/dex/dexInfo/ -L../../src/graphics/pictures/picCompression/ -L../../src/graphics/pictures/boundingBox/ -L../../src/graphics/bitplanes/ -L../../src/graphics/pixelOrder/ -L../../src/common/ptrs/
INCLUDE_PATHS   = -I../../src/

STD         = -std=c11
WARNINGS    = -Wall -Wextra -Wunused-macros -Wendif-labels
C_FLAGS     = -fno-common -fPIC -rdynamic
DEBUG       = -g
OPTIMIZA    = -Og

all: module

module: $(SOURCE_FILES)
	gcc -o $(MODULE_NAME).elf $(SOURCE_FILES) $(STD) $(WARNINGS) $(C_FLAGS) $(INCLUDE_PATHS) $(LIBS_PATHS) $(LIBS) $(DEBUG) $(OPTIMIZA)

clean:
	rm -f *.o *.elf *.a
