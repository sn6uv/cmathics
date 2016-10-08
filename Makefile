CC=gcc
FLAGS=-Wall -pedantic -std=c99 -g -I.

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

mathics: mathics.o
	$(CC) -o $@ $^ $(CFLAGS)
    
all: mathics

test: run_test
	./run_test

run_test: test.cpp
	g++ test.cpp -lgtest -o run_test

clean:
	rm -f *.o mathics
