CC=gcc
FLAGS=-Wall -std=c99 -I.

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

mathics: mathics.o
	$(CC) -o $@ $^ $(CFLAGS)
    
all: mathics

clean:
	rm -f *.o mathics
