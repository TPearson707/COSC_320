PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = BSToopTreaps.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

BSToopTreaps.o : BSToopTreaps.cpp
	$(CC) $(CPPFLAGS) -c BSToopTreaps.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
