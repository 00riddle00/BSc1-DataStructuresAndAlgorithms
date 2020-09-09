CC=gcc
CFLAGS=-Wall -Wextra -g -std=gnu11 -lm

pratybos9: pratybos9.c helpers.o
	$(CC) $(CFLAGS) -o pratybos9 pratybos9.c helpers.o

helpers.o: helpers.h helpers.c
	$(CC) $(CFLAGS) helpers.c -c

clean:
	rm pratybos9 
