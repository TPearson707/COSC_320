PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BSToopBalance.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BSToopBalance.o : BSToopBalance.cpp
	$(CC) $(CPPFLAGS) -c BSToopBalance.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
