CC=gcc
CPP=g++
FLAGS=-Wall -pedantic -std=c99 -g -I.
DEPS = types/expression.c types/symtable.c
OBJ = types/expression.o types/symtable.o

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

mathics: $(OBJ) mathics.o
	$(CC) -o $@ $^ $(CFLAGS)
    
test: run_test run_test_symtable
	./run_test
	./run_test_symtable

run_test: test.cpp $(OBJ)
	$(CPP) -c test.cpp -o test.o -Wall -pedantic -g -I,
	$(CPP) test.o $(OBJ) -lgtest -o run_test

run_test_symtable: test_symtable.cpp $(OBJ)
	$(CPP) -c test_symtable.cpp -o test_symtable.o -Wall -pedantic -g -I,
	$(CPP) test_symtable.o $(OBJ) -lgtest -o run_test_symtable

clean:
	rm -f mathics.o mathics
	rm -f $(OBJ)
