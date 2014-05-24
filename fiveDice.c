// Header information and system calls
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Function Definitions
void bannerDisplay();

// Struct to hold the points of individual players
struct player
{
	int score;
};

// Obvious main is obvious
int main(void)
{
	// Seed the random numbers
	srand(time(NULL));

	// Basic variables for the programs use
	int running = 1;
	int i, j;
	int rollNumber = 0;
	int rolledDice[5], heldValues[5];
	int numberHeld = 0;
	int toRoll = 5;
	int answer;
	char input[10], check;

	// Print out the opening banner
	bannerDisplay();

	// Main game(while) loop
	while(running)
	{
		// First for loop to set the random value of the dice
		for(i = 0; i < toRoll; i++)
		{
			rolledDice[i] = rand() % 6 + 1;
		}

		// Second for loop to print out the values of each dice,
		// Then to compare them to the other dice for matches
		for(i = 0; i < toRoll; i++)
		{
			printf("Dice %d: %d\n", i+1, rolledDice[i]);
		}

		// Increment the number of times player has rolled
		rollNumber++;

		// Loop to have player withhold dice from next roll
		while(answer != 0)
		{
			// Prompt for the dice to withhold
			printf("Which dice do you want to hold(0 for none): ");
			fgets(input, sizeof(input), stdin);
			sscanf(input, "%d", &answer);

			// Weed out unwelcome answers
			if(answer < 0 || answer > toRoll)
			{
				printf("That is not an acceptable value.\n");
				continue;
			}
			// Handle the legitimate cases
			else if(answer != 0)
			{
				// Set the number of dice available for roll to less
				toRoll--;

				// Confirm value to player and give value to heldValues array
				printf("Withholding value %d\n", rolledDice[answer-1]);
				heldValues[numberHeld] = rolledDice[answer-1];

				// Increase the number of values in array
				numberHeld++;
			}
		}

		// Reset the variable to prevent looping
		// There has to be a better solution than this
		answer = -1;

			// For loop to print out the values of held dice
		for(i = 0; i < numberHeld; i++)
		{
			printf("Held Dice %d: %d\n", i+1, heldValues[i]);
		}


/*
		// Ask the player if they want to roll again
		while(check != 'n' && check != 'y')
		{
			printf("\nDo you wish to roll again?[y/N]: ");
			fgets(input, sizeof(input), stdin);

			// Parse input to lowercase
			check = tolower(input[0]);
		}
*/
		// React to player input
		if(check == 'n')
		{
			running = 0;
		}
		else
		{
			check = 'y';
			// check = '\0';
		}
	}

	// End of program
	return 0;
}

// Opening banner to welcome users
void bannerDisplay()
{
	printf("\n");
	printf(" ____ _____      ______   ____ ___ ___ ____\n");
	printf("|  __|_ _\\ \\    / / ___| |  _ \\_ _/ __| ___|\n");
	printf("| |_  | | \\ \\  / /|  _|  | | | | | |  |  _|\n");
	printf("|  _| | |  \\ \\/ / | |__  | |_| | | |__| |__\n");
	printf("|_|  |___|  \\__/  |____| |____/___\\___|____|\n");
	printf("\n");
	printf("A Game of Luck and Skill.\n");
	printf("\n");
}	
