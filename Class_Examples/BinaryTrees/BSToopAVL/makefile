PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BSToopAVL.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BSToopAVL.o : BSToopAVL.cpp
	$(CC) $(CPPFLAGS) -c BSToopAVL.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
