// Use the custom header file
#include "fiveDice.h"

// Obvious main is obvious
int main(void)
{
	// Seed the random numbers
	srand(time(NULL));

	// Print out the opening banner
	bannerDisplay();

	// Run the main loop of the program
	gameLoop();

	// End of program
	return 0;
}

// Bottleneck function for the rest of the program
// Could put all of this in main, but I feel this is better for organization
void gameLoop()
{
	/* Program variables
	 * These are going to be prominent throughout, instead of one time use 
	 * Which are prominent in the other functions */
	int running = 1;
	int rolledDice[DICENUMBER], heldValues[DICENUMBER];
	int numberHeld = 0;
	int toRoll = DICENUMBER;
	char choice;

	// Set up the dice and the player
	helpDisplay();
	diceRoll(rolledDice, toRoll);
	printDice(rolledDice, toRoll, heldValues, numberHeld);

	// Main loop for entire game
	while(running)
	{
		// Call the input function to get player option
		choice = handleInput();

		// Switch statement to handle player choice
		switch(choice)
		{
			// Call the help display function
			case 'h':
				helpDisplay();
				break;

			// Call dice rolling function
			case 'd':
				diceRoll(rolledDice, toRoll);

			// Call printing function
			case 'p':
				printDice(rolledDice, toRoll, heldValues, numberHeld);
				break;

			// Call the withholding function
			case 'w':
				toRoll = withholdDice(rolledDice, heldValues, &numberHeld, toRoll);
				break;

			// Call the replace function
			case 'r':
				toRoll = replaceDice(rolledDice, heldValues, &numberHeld, toRoll);
				break;

			// Quit the program
			case 'q':
				running = 0;
				break;

			// Discard all other cases
			default:
				break;
		}
	}

	return;
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

// Function to print out the help option to players
void helpDisplay()
{
	printf("h - This help page\n");
	printf("d - Roll the dice\n");
	printf("p - Print the dice on the screen\n");
	printf("w - Withhold dice from the table to your hand\n");
	printf("r - Return dice from your hand to the cup\n");

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
void printDice(int rolledDice[], int toRoll, int heldValues[], int numberHeld)
{
	// Function variables
	int i;

	if(numberHeld > 0)
	{
		// Print out new line for cleanliness
		printf("\n");

		// Print out the dice that are held by the player
		for(i = 0; i < numberHeld; i++)
		{
			printf("Held Dice %d: %d\n", i+1, heldValues[i]);
		}
	}

	// Print new line for cleanliness
	printf("\n");

	if(toRoll == 0)
	{
		return;
	}

	// Print out the dice that were just rolled
	for(i = 0; i < toRoll; i++)
	{
		printf("Dice %d: %d\n", i+1, rolledDice[i]);
	}

	// Print new line for cleanliness
	printf("\n");

	// Obligatory return
	return;
}

// Function to handle the player's choice to withhold dice
int withholdDice(int *rolledDice, int *heldValues, int *numberHeld, int toRoll)
{
	// Function variables
	int answer = -1;
	char input[5];

	// Print out new line for cleanliness
	printf("\n");

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

	// Print new line for cleanliness
	printf("\n");

	// Pad down array values for printing function
	arrayShrink(rolledDice, DICENUMBER);

	// Return the value to be used by toRoll
	return DICENUMBER - *numberHeld;
}

int replaceDice(int *rolledDice, int *heldValues, int *numberHeld, int toRoll)
{
	// Function variables 
	int answer = -1;
	char input[5];
	int replace = 0;

	// Use the printDice function to only show held dice
	printDice(rolledDice, 0, heldValues, *numberHeld);

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
			replace += 1;
		}
	}

	// Set the numberHeld variable to it's proper value
	*numberHeld -= replace;

	// Print a new line for cleanliness
	printf("\n");

	// Push the values in heldValues to lowest possible index
	arrayShrink(heldValues, DICENUMBER);

	// Return the amount of dice allowed to roll
	return DICENUMBER - *numberHeld;
}

char handleInput()
{
	// Function variables
	char input[5];
	char answer;

	// Take input from the player
	printf(":");
	fgets(input, sizeof(input), stdin);
	answer = tolower(input[0]);

	// Return the value wanted
	return answer;
}
