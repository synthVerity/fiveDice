// Header information and system calls
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Function Definitions
void bannerDisplay();
void diceRoll(int *rolledDice, int toRoll);
void printDice(int rolledDice[], int toRoll, int *rollNumber);

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
	int rollNumber = 1;
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
		// Call dice rolling function
		diceRoll(rolledDice, toRoll);

		// Call printing function
		printDice(rolledDice, toRoll, &rollNumber);
		
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
				// Check the player for trying to cheat
				if(rolledDice[answer-1] == 0)
				{
					printf("You already witheld that dice.\n");
					continue;
				}

				// Confirm value to player and give value to heldValues array
				printf("Withholding value %d\n", rolledDice[answer-1]);
				heldValues[numberHeld] = rolledDice[answer-1];

				// Set value of dice withheld to zero
				// Used to stop player from spamming same dice
				rolledDice[answer-1] = 0;

				// Increase the number of values in array
				numberHeld++;
			}
		}

		// Reset the variable to prevent looping
		// There has to be a better solution than this
		answer = -1;

		// Set the number allowed to roll
		// Need a better solution down the road
		toRoll = 5 - numberHeld;

			// For loop to print out the values of held dice
		for(i = 0; i < numberHeld; i++)
		{
			printf("Held Dice %d: %d\n", i+1, heldValues[i]);
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

// Function for the dice roll
void diceRoll(int *rolledDice, int toRoll)
{
	// Function variables
	int i;

	// Actual loop to set values
	for(i = 0; i < toRoll; i++)
	{
		rolledDice[i] = rand() % 6 + 1;
	}
}

// Function to print out the values of the dice in the last roll
void printDice(int rolledDice[], int toRoll, int *rollNumber)
{
	// Function variables
	int i;

	// Print out the number of the roll
	printf("This is roll number %d.\n", *rollNumber);

	// Actual printing loop
	for(i = 0; i < toRoll; i++)
	{
		printf("Dice %d: %d\n", i+1, rolledDice[i]);
	}

	// Update the roll number to reflect roll
	*rollNumber += 1;
}
