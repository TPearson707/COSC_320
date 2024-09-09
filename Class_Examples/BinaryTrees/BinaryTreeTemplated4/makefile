PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BinaryTreeTemplated4.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BinaryTreeTemplated4.o : BinaryTreeTemplated4.cpp
	$(CC) $(CPPFLAGS) -c BinaryTreeTemplated4.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
