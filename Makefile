CC=g++

CFLAGS=-c -Wall

all: BipartiteMatching

matching: main.o BipartiteMatching.o MaxumumFlow.o
	$(CC) main.o BipartiteMatching.o MaximumFlow.o -o matching

main.o: main.cpp BipartiteMatching.hpp
	$(CC) $(CFLAGS) main.cpp -o main.o

BipartiteMatching.o: BipartiteMatching.cpp BipartiteMatching.hpp MaximumFlow.hpp
	$(CC) $(CFLAGS) BipartiteMatching.cpp -o BipartiteMatching.o

MaximumFlow.o: MaximumFlow.cpp MaximumFlow.hpp
	$(CC) $(CFLAGS) MaximumFlow.cpp -o MaximumFlow.o

clean:
	rm -rf *o start
