fiveDice : fiveDice.o
	gcc -o fiveDice fiveDice.o

fiveDice.o : fiveDice.c
	gcc -c fiveDice.c

clean :
	rm fiveDice *.o

debug :
	gcc -pg -g fiveDice.c
