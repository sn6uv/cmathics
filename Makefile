CC=gcc
CPP=g++
FLAGS=-Wall -pedantic -std=c99 -g -I.
DEPS = types/expression.c types/symtable.c
OBJ = types/expression.o types/symtable.o

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

mathics: $(OBJ) mathics.o
	$(CC) -o $@ $^ $(CFLAGS)
    
test: test_expression test_symtable
	./test_expression
	./test_symtable

test_expression: test_expression.cpp $(OBJ)
	$(CPP) -c test_expression.cpp -o test_expression.o -Wall -pedantic -g -I.
	$(CPP) test_expression.o $(OBJ) -lgtest -o test_expression

test_symtable: test_symtable.cpp $(OBJ)
	$(CPP) -c test_symtable.cpp -o test_symtable.o -Wall -pedantic -g -I.
	$(CPP) test_symtable.o $(OBJ) -lgtest -o test_symtable

clean:
	rm -f mathics.o mathics
	rm -f $(OBJ)
