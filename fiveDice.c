#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	srand(time(NULL));

	int i;
	int dice[5];

	for(i = 0; i < 5; i++)
	{
		dice[i] = rand() % 6 + 1;
	}

	for(i = 0; i < 5; i++)
	{
		printf("Dice %d: %d\n", i+1, dice[i]);
	}

	return 0;
}
