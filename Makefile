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
    
test: test_expression test_definitions test_stack
	./test_expression
	./test_definitions
	./test_stack

test_expression: test_expression.cpp $(OBJ)
	$(CPP) -c test_expression.cpp -o test_expression.o -Wall -pedantic -g -I.
	$(CPP) test_expression.o $(OBJ) -o test_expression -lgtest $(LINKS)

test_definitions: test_definitions.cpp $(OBJ)
	$(CPP) -c test_definitions.cpp -o test_definitions.o -Wall -pedantic -g -I.
	$(CPP) test_definitions.o $(OBJ) -o test_definitions -lgtest $(LINKS)

test_stack: test_stack.cpp core/data_structures/stack.o
	$(CPP) -c test_stack.cpp -o test_stack.o -Wall -pedantic -g -I.
	$(CPP) test_stack.o core/data_structures/stack.o -o test_stack -lgtest $(LINKS)

clean:
	rm -f mathics.o mathics
	rm -f $(OBJ)
