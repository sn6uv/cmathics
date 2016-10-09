CC=gcc
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
	g++ test.cpp -lgtest -o run_test

run_test_symtable: test_symtable.cpp $(OBJ)
	g++ test_symtable.cpp $(OBJ) -lgtest -o run_test_symtable


clean:
	rm -f mathics.o mathics
	rm -f $(OBJ)
