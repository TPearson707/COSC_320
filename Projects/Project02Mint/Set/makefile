# makefile created by Thomas Pearson 04/17/2024
PROG = prog
CC = g++
CPPFLAGS = -g -Wall
OBJS = main.o

${PROG} : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o :
	$(CC) $(CPPFLAGS) -c main.cpp

clean :
	rm -f core $(PROG) $(OBJS)

rebuild:
	make
	make clean
