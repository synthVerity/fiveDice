// Use the custom header file
#include "fiveDice.h"

// Obvious main is obvious
int main(void)
{
	// Variable for number of players
	int players;

	// Seed the random numbers
	srand(time(NULL));

	// Set up the number of players
	players = gameSetup();

	// Print out the opening banner
	bannerDisplay();

	// Run the main loop of the program
	gameLoop(players);

	// End of program
	return 0;
}

// Bottleneck function for the rest of the program
// Could put all of this in main, but I feel this is better for organization
void gameLoop(int players)
{
	/* Program variables
	 * These are going to be prominent throughout, instead of one time use 
	 * Which are used in the other functions */
	int running = 1;
	int rolledDice[DICENUMBER], heldValues[DICENUMBER];
	int numberHeld = 0;
	int toRoll = DICENUMBER;
	int curPlayer = 1, turn = 1;
	char choice;

	// Take structs from header file for scorecards
	Scorecard scorecards[players];

	// Set up the dice and the player
	helpDisplay();
	diceRoll(rolledDice, toRoll);
	printDice(rolledDice, toRoll, heldValues, numberHeld);
	whosTurn(players, curPlayer, turn);

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
			case 'r':
				// Set the values for turn and current player
				if(turn < 3)
				{
					turn++;
				}
				else
				{
					turn = 1;
					toRoll = DICENUMBER;
					numberHeld = 0;
					if(curPlayer < players)
					{
						curPlayer++;
					}
					else
					{
						curPlayer = 1;
					}
				}

				// Roll the dice
				diceRoll(rolledDice, toRoll);

			// Call printing function
			case 'p':
				printDice(rolledDice, toRoll, heldValues, numberHeld);
				whosTurn(players, curPlayer, turn);
				break;

			// Call the withholding function
			case 'w':
				toRoll = withholdDice(rolledDice, heldValues, &numberHeld, toRoll);
				break;

			// Call the replace function
			case 'd':
				toRoll = replaceDice(rolledDice, heldValues, &numberHeld, toRoll);
				break;

			case 'c':
				cashOut(scorecards, curPlayer);
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

// Function to set up the game from the beginning
int gameSetup()
{
	// Function variables
	int answer = -1;
	char input[5];

	while(answer < 1 || answer > 9)
	{
		// Ask how many players there will be
		printf("How many players will be participating?: ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%d", &answer);
	}

	// Return the amount of players
	return answer;
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
	printf("r - Roll the dice\n");
	printf("p - Print the dice on the screen\n");
	printf("w - Withhold dice from the table to your hand\n");
	printf("d - Return dice from your hand to the cup\n");
	printf("c - Cash out points onto your scorecard\n");
	printf("q - Quits the game\n");

	// Obligatory return
	return;
}

// Function to print out who's turn it is
void whosTurn(int players, int curPlayer, int turn)
{
	// Print out the current player and turn
	printf("It is player %d's turn number %d.\n", curPlayer, turn);

	// End the function
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

	// Print out who's turn it is
	

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

// Function to apply player points to scorecard
void cashOut(Scorecard *scorecard, int curPlayer)
{
	scorecard[curPlayer].score = 0;
	printf("%d\n", scorecard[curPlayer].score);

	return;
}

// Function for handling main game input
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
