CC=gcc
CFLAGS=-Wall -Wextra -lm -g -std=gnu11

main: main.c numbers.o
	$(CC) $(CFLAGS) -o main main.c numbers.o -L. -l_riddle

numbers.o: numbers.h numbers.c

clean:
	rm -f main numbers.o
