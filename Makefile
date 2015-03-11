CC=gcc
CFLAGS=-Wall -std=c99 -g
LDFLAGS=
EXEC=sudokusolver

all: $(EXEC)

sudokusolver: sudokusolver.o interface_io.o verification.o

sudokusolver.o: sudokusolver.c interface_io.h

interface_io.o: interface_io.c interface_io.h 

verification_io.o: verification_io.c verification_io.h 

clean:
	rm -f *.o core

