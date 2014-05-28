CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=gnu99

fiveDice : fiveDice.o
	$(CC) -o fiveDice fiveDice.o $(CFLAGS)

fiveDice.o : fiveDice.c fiveDice.h
	$(CC) -c -Wall fiveDice.c $(CFLAGS)

clean :
	rm fiveDice *.o

debug :
	$(CC) -pg -g fiveDice.c $(CFLAGS)
