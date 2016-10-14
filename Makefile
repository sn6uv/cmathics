CC=gcc
FLAGS=-Wall -pedantic -std=c99 -g -I.
LINKS=-lgmp -lmpfr

DEPS = $(wildcard core/*.c)
OBJS = $(patsubst %.c,%.o,$(DEPS))

CPP=g++
TEST_FLAGS=-Wall -pedantic -g -I.
TEST_LINKS=-lgtest -lgmpxx

TEST_DEPS = $(wildcard tests/*.cpp)
TEST_OBJS = $(patsubst %.cpp,%.o,$(TEST_DEPS))

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

%.o: %.cpp
	$(CPP) -c -o $@ $< $(TEST_FLAGS)

mathics: $(OBJS) mathics.o
	$(CC) -o $@ $^ $(FLAGS) $(LINKS)

test: $(TEST_OBJS) $(OBJS)
	$(CPP) -o $@ $^ $(TEST_FLAGS) $(TEST_LINKS) $(LINKS)

run_test: test
	./test

clean:
	rm -f mathics test $(OBJS) $(TEST_OBJS) mathics.o
