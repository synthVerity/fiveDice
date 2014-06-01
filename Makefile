CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=gnu99

fiveDice : fiveDice.o arrayFunc.o
	$(CC) -o fiveDice fiveDice.o arrayFunc.o $(CFLAGS)

fiveDice.o : fiveDice.c fiveDice.h arrayFunc.c arrayFunc.h
	$(CC) -c fiveDice.c arrayFunc.c $(CFLAGS)

clean :
	rm fiveDice *.o

debug :
	$(CC) -pg -g fiveDice.c arrayFunc.c $(CFLAGS)
