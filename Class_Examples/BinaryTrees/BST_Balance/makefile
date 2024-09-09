PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BST_Balance.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BST_Balance.o : BST_Balance.cpp
	$(CC) $(CPPFLAGS) -c BST_Balance.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
