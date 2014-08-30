CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=gnu99

all : fiveDice.o arrayFunc.o
	$(CC) -o fivedice fiveDice.o arrayFunc.o $(CFLAGS)

fivedice : fiveDice.o
	$(CC) fiveDice.o $(CFLAGS)

arrayFunc : arrayFunc.o
	$(CC) arrayFunc.o $(CFLAGS)

fiveDice.o : fiveDice.c fiveDice.h
	$(CC) -c fiveDice.c $(CFLAGS)

arrayFunc.o : arrayFunc.c arrayFunc.h
	$(CC) -c arrayFunc.c $(CFLAGS)

clean :
	rm fiveDice *.o

debug :
	$(CC) -pg -g fiveDice.c arrayFunc.c $(CFLAGS)
