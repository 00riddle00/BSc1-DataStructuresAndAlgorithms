CC=g++
CFLAGS=-Wall -Wextra -g -std=c++11

demo: demo.cpp hash_table.o #binary_search_tree.o
	$(CC) $(CFLAGS) -o demo demo.cpp hash_table.o #binary_search_tree.o

binary_search_tree.o: binary_search_tree.h binary_search_tree.cpp
	$(CC) $(CFLAGS) binary_search_tree.cpp -c

hash_table.o: hash_table.h hash_table.cpp
	$(CC) $(CFLAGS) hash_table.cpp -c

clean:
	rm demo hash_table.o binary_search_tree.o
