all: module

module: toBmp.c toBmp.h
	gcc -std=c11 -Wall -Wextra -g -fno-common toBmp.c -c

module_test: module toBmp_test.c
	gcc -std=c11 -Wall -Wextra -g -fno-common toBmp.o toBmp_test.c -o toBmp_test.elf
