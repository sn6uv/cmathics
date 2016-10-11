CC=gcc
FLAGS=-Wall -pedantic -std=c99 -g -I.
LINKS=-lgmp -lmpfr

DEPS = $(wildcard core/*.c)
OBJS = $(patsubst %.c,%.o,$(DEPS))

CPP=g++
TEST_FLAGS=-Wall -pedantic -g -I.
TEST_LINKS=-lgtest

TEST_DEPS = $(wildcard tests/*.cpp)
TEST_OBJS = $(patsubst %.cpp,%.o,$(TEST_DEPS))
TESTS = $(patsubst %.cpp,%.test,$(TEST_DEPS))

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

%.o: %.cpp
	$(CPP) -c -o $@ $< $(TEST_FLAGS)

%.test: %.o $(OBJS)
	$(CPP) -o $@ $^ $(TEST_LINKS) $(LINKS)

mathics: $(OBJS) mathics.o
	$(CC) -o $@ $^ $(FLAGS) $(LINKS)
    
test: $(TESTS)
	$(foreach var,$(TESTS),./$(var);)

clean:
	rm -f mathics $(OBJS) $(TEST_OBJS) $(TESTS)
