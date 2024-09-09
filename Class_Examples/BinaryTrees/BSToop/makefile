PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BSToop.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BSToop.o : BSToop.cpp
	$(CC) $(CPPFLAGS) -c BSToop.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
