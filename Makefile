CC=gcc
CPPFLAGS=-Isrc
CFLAGS=-Wextra -Werror -Wvla -Wall -pedantic -std=c99

LDLIBS=-lcriterion

OBJ=src/utils/date/date.o 
TESTOBJ=tests/date/date.o

all: $(OBJ)
	$(CC) $(OBJ) -o task_manager

check: $(OBJ) $(TESTOBJ)
	$(CC) $(OBJ) $(TESTOBJ) $(LDLIBS) -o testsuite
	./testsuite

clean:
	$(RM) $(OBJ) $(TESTOBJ) testsuite task_manager
