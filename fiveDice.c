// Use the custom header file
#include "fiveDice.h"

// Obvious main is obvious
int main(void)
{
	// Seed the random numbers
	srand(time(NULL));

	// Basic variables for the programs use
	int running = 1;
	int rollNumber = 1;
	int rolledDice[DICENUMBER], heldValues[DICENUMBER];
	int numberHeld = 0;
	int toRoll = DICENUMBER;

	// Print out the opening banner
	bannerDisplay();

	// Main game(while) loop
	while(running)
	{
		// Call dice rolling function
		diceRoll(rolledDice, toRoll);

		// Call printing function
		printDice(rolledDice, toRoll, &rollNumber, heldValues, numberHeld);

		// Call the withholding function
		toRoll = withholdDice(rolledDice, heldValues, &numberHeld, toRoll);	

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

	// Obligatory return
	return;
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

	// Obligatory return
	return;
}

// Function to print out the values of the dice in the last roll
void printDice(int rolledDice[], int toRoll, int *rollNumber, int heldValues[], int numberHeld)
{
	// Function variables
	int i;

	// Print out the number of the roll
	printf("This is roll number %d.\n", *rollNumber);

	// Print new line for cleanliness
	printf("\n");

	// Print out the dice that are held by the player
	for(i = 0; i < numberHeld; i++)
	{
		printf("Held Dice %d: %d\n", i+1, heldValues[i]);
	}

	// Print new line for cleanliness
	printf("\n");

	// Print out the dice that were just rolled
	for(i = 0; i < toRoll; i++)
	{
		printf("Dice %d: %d\n", i+1, rolledDice[i]);
	}

	// Print new line for cleanliness
	printf("\n");

	// Update the roll number to reflect roll
	*rollNumber += 1;

	// Obligatory return
	return;
}

// Function to handle the player's choice to withhold dice
int withholdDice(int *rolledDice, int *heldValues, int *numberHeld, int toRoll)
{
	// Function variables
	int answer = -1;
	char input[5];

	// Loop until player gets all the dice they want
	while(answer != 0)
	{
		// Prompt the player for the dice and take input
		printf("Which dice do you want to hold(0 for none): ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%d", &answer);

		// Weed out the bad input values
		if(answer < 0 || answer > toRoll)
		{
			printf("That is not an acceptable value.\n");
			continue;
		}
		// Handle the legitimate input
		else if(answer != 0)
		{
			// Stop player from spamming same dice
			if(rolledDice[answer-1] == 0)
			{
				printf("You have already withheld that dice.\n");
				continue;
			}

			// Print out the value to player
			printf("Withholding value %d.\n", rolledDice[answer-1]);

			// Take the value over from dice array to values array
			heldValues[*numberHeld] = rolledDice[answer-1];

			// Remove the dice to prevent player cheating
			rolledDice[answer-1] = 0;

			// Increment the number held for array
			*numberHeld += 1;

		}
	}

	// Reset answer for the next part and new line for cleanliness
	answer = -1;
	printf("\n");

	// Run the same basic process, but to return dice to roll
	while(answer != 0)
	{
		// Promt player for the dice and take input
		printf("Which dice do you want to replace(0 for none): ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%d", &answer);

		// Weed out the bad input values
		if(answer < 0 || answer > *numberHeld)
		{
			printf("That is not an acceptable value.\n");
			continue;
		}
		// Handle the legitamate input
		else if(answer != 0)
		{
			// Stop the player from spamming same dice
			if(heldValues[answer-1] == 0)
			{
				printf("You have already replaced that dice.\n");
				continue;
			}

			// Print out the value to the player
			printf("Replacing value %d.\n", heldValues[answer-1]);

			// Take the value from values array, and add to the dice array
			heldValues[answer-1] = 0;
			*numberHeld -= 1;
		}
	}

	// Push the values in heldValues to lowest possible index
	// Passing is possibly convoluted, trying to eliminate magic numbers
	arrayShrink(heldValues, DICENUMBER);

	// Print a new line for cleanliness
	printf("\n");

	// Return the value to be used by toRoll
	return DICENUMBER - *numberHeld;
}
