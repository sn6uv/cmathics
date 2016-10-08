CC=gcc
FLAGS=-Wall -pedantic -std=c99 -g -I.

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

mathics: mathics.o
	$(CC) -o $@ $^ $(CFLAGS)
    
all: mathics

clean:
	rm -f *.o mathics
