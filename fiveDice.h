// Make sure I don't overuse this file
#ifndef FIVEDICE_H
#define FIVEDICE_H

// System header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "arrayFunc.h"

// Struct for player information
typedef struct
{
	// Hold player's score here
	int score;
	int ones;
	int twos;
	int threes;
	int fours;
	int fives;
	int sixes;
	int topBonus;
	int threeOfKind;
	int fourOfKind;
	int fullHouse;
	int smallStraight;
	int largeStraight;
	int fiveOfKind;
	int chance;
} Scorecard;

// Function definitions
void gameLoop(int players);
int gameSetup();
void bannerDisplay();
void helpDisplay();
void whosTurn(int players, int curPlayer, int turn);
void diceRoll(int *rolledDice, int toRoll);
void printDice(int rolledDice[], int toRoll, int heldValues[], int numberHeld);
int withholdDice(int *rolledDice, int *heldValues, int *numberHeld, int toRoll);
int replaceDice(int *rolledDice, int *heldValues, int *numberHeld, int toRoll);
void cashOut(Scorecard *scorecard, int curPlayer);
char handleInput();

// Setting up a constant for the number of dice being rolled
#define DICENUMBER 5

// End the header file and if
#endif
