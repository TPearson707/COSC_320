PROG = timesorts
OBJS = sortTiming.o
FLAG = -g -Wall -std=c++11
CC = g++

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

sortTiming.o: sortTiming.cpp
	$(CC) $(FLAG) -c sortTiming.cpp

clean:
	rm -f core $(PROG) $(OBJS)
