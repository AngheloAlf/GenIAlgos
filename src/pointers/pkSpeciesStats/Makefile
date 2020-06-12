MODULE_NAME = pkStatsByDex

all: module

module: $(MODULE_NAME).c $(MODULE_NAME).h
	gcc -std=c11 -Wall -Wextra -g -fno-common $(MODULE_NAME).c -c -o $(MODULE_NAME).o
	@echo 

module_test: module $(MODULE_NAME)_test.c
	gcc -std=c11 -Wall -Wextra -g -fno-common $(MODULE_NAME).o $(MODULE_NAME)_test.c -o $(MODULE_NAME).elf
