PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = RBTreeEx.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

RBTreeEx.o : RBTreeEx.cpp
	$(CC) $(CPPFLAGS) -c RBTreeEx.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
