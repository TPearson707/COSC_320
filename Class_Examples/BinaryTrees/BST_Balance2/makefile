PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BST_Balance2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BST_Balance2.o : BST_Balance2.cpp
	$(CC) $(CPPFLAGS) -c BST_Balance2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
