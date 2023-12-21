CC=gcc
CFLAGS=-Wextra -Werror -Wvla -Wall -pedantic -std=c99

INCLUDE=-Isrc

OBJ=src/utils/date/date.o 
TESTOBJ=tests/date/date.o

all: $(OBJ)
	$(CC) $(OBJ) -o task_manager
