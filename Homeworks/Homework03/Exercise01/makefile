# Makefile created by Thomas Pearson on 2/21/2024
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
	make clean
	make
