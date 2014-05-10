CC = gcc

CFLAGS  = -std=c99 -g -Wall -O3 $(shell pkg-config --cflags cunit)

LDFLAGS = $(shell pkg-config --libs cunit)

.PHONY:
default: main

.PHONY:
test: test-inversion-counter

test-inversion-counter: inversion-counter.h inversion-counter.o

main: inversion-counter.h inversion-counter.o

inversion-counter.o: inversion-counter.h

.PHONY:
all: clean default test

.PHONY:
clean:
	rm -f *.o *.*~ main test-inversion-counter
