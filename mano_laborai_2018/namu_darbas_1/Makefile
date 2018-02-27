CC=g++
CFLAGS=-Wall -Wextra -g 

main: main.cpp numbers.o
	$(CC) $(CFLAGS) -o main main.cpp numbers.o -L. -l_riddle_cpp

numbers.o: numbers.h numbers.cpp

clean:
	rm -f main numbers.o
