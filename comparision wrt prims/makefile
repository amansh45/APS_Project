CC=g++
Main: binomial_heap.o avl.o rb_tree.o main.o
	$(CC) binomial_heap.o avl.o rb_tree.o main.o -o Main

main.o: main.cpp headers.h
	$(CC) -std=c++11 -c main.cpp

binomial_heap.o: binomial_heap.cpp headers.h
	$(CC) -std=c++11 -c binomial_heap.cpp

avl.o: avl.cpp headers.h
	$(CC) -std=c++11 -c avl.cpp

rb_tree.o: rb_tree.cpp headers.h
	$(CC) -std=c++11 -c rb_tree.cpp