CC=g++

CFLAGS=-c -Wall

all: start

start: main.o BipartiteMatching.o
	$(CC) main.o BipartiteMatching.o -o start

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

BipartiteMatching.o: BipartiteMatching.cpp MaxumumFlow.o
	$(CC) $(CFLAGS) BipartiteMatching.cpp BipartiteMatching.hpp MaxumumFlow.o

MaxumumFlow.o: MaxumumFlow.cpp MaxumumFlow.hpp
	$(CC) $(CFLAGS) MaxumumFlow.cpp MaxumumFlow.hpp

clean:
	rm -rf *o start
