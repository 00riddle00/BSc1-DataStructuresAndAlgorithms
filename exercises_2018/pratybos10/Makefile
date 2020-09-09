CC=gcc
CFLAGS=-Wall -Wextra -g -std=gnu11 -lm

pratybos10: pratybos10.c helpers.o
	$(CC) $(CFLAGS) -o pratybos10 pratybos10.c helpers.o

helpers.o: helpers.h helpers.c
	$(CC) $(CFLAGS) helpers.c -c

clean:
	rm pratybos10 helpers.o 
