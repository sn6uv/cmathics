CC=gcc
CPP=g++
FLAGS=-Wall -pedantic -std=c99 -g -I.
DEPS = core/expression.c core/definitions.c core/formatter.c core/int.c
OBJ = core/expression.o core/definitions.o core/formatter.o core/int.o

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

mathics: $(OBJ) mathics.o
	$(CC) -o $@ $^ $(CFLAGS)
    
test: test_expression test_definitions
	./test_expression
	./test_definitions

test_expression: test_expression.cpp $(OBJ)
	$(CPP) -c test_expression.cpp -o test_expression.o -Wall -pedantic -g -I.
	$(CPP) test_expression.o $(OBJ) -lgtest -o test_expression

test_definitions: test_definitions.cpp $(OBJ)
	$(CPP) -c test_definitions.cpp -o test_definitions.o -Wall -pedantic -g -I.
	$(CPP) test_definitions.o $(OBJ) -lgtest -o test_definitions

clean:
	rm -f mathics.o mathics
	rm -f $(OBJ)
