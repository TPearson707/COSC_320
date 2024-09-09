PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BSToopKd.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BSToopKd.o : BSToopKd.cpp
	$(CC) $(CPPFLAGS) -c BSToopKd.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
