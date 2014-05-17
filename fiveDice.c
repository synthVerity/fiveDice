// Header information and system calls
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Obvious main is obvious
int main(void)
{
	// Seed the random numbers
	srand(time(NULL));

	// Basic variables for the programs use
	int running = 1;
	int i, j;
	int dice[5];
	char input;

	// Main game(while) loop
	while(running)
	{
		// First for loop to set the random value of the dice
		for(i = 0; i < 5; i++)
		{
			dice[i] = rand() % 6 + 1;
		}

		// Second for loop to print out the values of each dice,
		// Then to compare them to the other dice for matches
		for(i = 0; i < 5; i++)
		{
			printf("Dice %d: %d\t", i+1, dice[i]);

			// Nested for loop to compare the values of the dice
			for(j = 0; j < 5; j++)
			{
				// Check to see if the dice match, and that it is not the same dice
				if(dice[i] == dice[j] && i != j)
				{
					printf("Equal to dice %d  ", j+1);
				}
			}

			// New line to keep dice seperate
			printf("\n");
		}

		// Ask the player if they want to roll again
		while(input != 'n' && input != 'y')
		{
			printf("\nDo you wish to roll again?[y/N]: ");
			scanf("%c", &input);

			// Parse input to lowercase
			input = tolower(input);
		}

		// React to player input
		if(input == 'n')
		{
			running = 0;
		}
		else
		{
			input = 0;
		}
	}

	// End of program
	return 0;
}
