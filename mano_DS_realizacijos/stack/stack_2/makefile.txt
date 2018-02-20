CC = gcc

# to object file:
mod.o: mod.s
	gcc -g -c mod.s -o mod.o

# to assembly code	
mod.s: mod.i
	gcc -g -S mod.i -o mod.s

# to preprocessed source code
mod.i: mod.c
	gcc -g -E mod.c -o mod.i

# to executable
test: test.c mod.o
	gcc -g test.c mod.o -o test

clean:
	rm -f mod.i mod.o mod.s test

clean_all:
	rm *.i *.o *.s *.exe

rebuild: clean test
