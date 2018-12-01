CC=g++
CFLAGS=-Wall -Wextra -g -std=c++11
#CFLAGS=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

all: numbers.o demo #test #helpers.o #demo_ui

#test: test.cpp numbers.o
	#$(CC) $(CFLAGS) -o test test.cpp numbers.o

demo: demo.cpp numbers.o
	$(CC) $(CFLAGS) -o demo demo.cpp numbers.o 

#demo_ui: demo_ui.cpp helpers.o numbers.o
#	$(CC) $(CFLAGS) -o demo_ui demo_ui.cpp helpers.o numbers.o 

#helpers.o: helpers.h helpers.cpp
#	$(CC) $(CFLAGS) helpers.cpp -c

numbers.o: numbers.h numbers.cpp
	$(CC) $(CFLAGS) numbers.cpp -c

clean:
	rm -f demo_ui demo numbers.o test #helpers.o

rebuild: clean all

