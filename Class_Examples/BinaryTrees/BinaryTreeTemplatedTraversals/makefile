PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BinaryTreeTemplatedTraversals.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BinaryTreeTemplatedTraversals.o : BinaryTreeTemplatedTraversals.cpp
	$(CC) $(CPPFLAGS) -c BinaryTreeTemplatedTraversals.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
