CC=gcc
CPP=g++
FLAGS=-Wall -pedantic -std=c99 -g -I.
LINKS=-lgmp -lmpfr
DEPS = $(wildcard core/*.c)
OBJ = $(patsubst %.c,%.o,$(wildcard core/*.c))

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

mathics: $(OBJ) mathics.o
	$(CC) -o $@ $^ $(CFLAGS) $(LINKS)
    
test: test_expression test_definitions
	./test_expression
	./test_definitions

test_expression: test_expression.cpp $(OBJ)
	$(CPP) -c test_expression.cpp -o test_expression.o -Wall -pedantic -g -I.
	$(CPP) test_expression.o $(OBJ) -o test_expression -lgtest $(LINKS)

test_definitions: test_definitions.cpp $(OBJ)
	$(CPP) -c test_definitions.cpp -o test_definitions.o -Wall -pedantic -g -I.
	$(CPP) test_definitions.o $(OBJ) -o test_definitions -lgtest $(LINKS)

clean:
	rm -f mathics.o mathics
	rm -f $(OBJ)
