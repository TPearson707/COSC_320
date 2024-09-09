PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BSToopAVL2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BSToopAVL2.o : BSToopAVL2.cpp
	$(CC) $(CPPFLAGS) -c BSToopAVL2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
