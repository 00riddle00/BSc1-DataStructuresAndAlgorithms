CC=gcc
CFLAGS=-Wall -Wextra -g -std=gnu11

all: hash_table_1 hash_table_2

hash_table_1: hash_table_1.c
	gcc -o hash_table_1 hash_table_1.c -L${LD_LIBRARY_PATH} -l_riddle 

hash_table_2: hash_table_2.c
	gcc -o hash_table_2 hash_table_2.c -L${LD_LIBRARY_PATH} -l_riddle 

clean:
	rm hash_table_1 hash_table_2
