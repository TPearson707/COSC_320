PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BinaryTreeDeleteByCopy.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BinaryTreeDeleteByCopy.o : BinaryTreeDeleteByCopy.cpp
	$(CC) $(CPPFLAGS) -c BinaryTreeDeleteByCopy.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
