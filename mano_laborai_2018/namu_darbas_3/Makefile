CC=gcc
CFLAGS=-Wall -Wextra -g -std=gnu11

demo: demo.c
	gcc -o demo demo.c -L${LD_LIBRARY_PATH} -l_riddle -l_sorting

clean:
	rm demo
