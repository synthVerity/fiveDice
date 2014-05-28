// Make sure I don't overuse this file
#ifndef FIVEDICE_H
#define FIVEDICE_H

// System header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Function definitions
void bannerDisplay();
void diceRoll(int *rolledDice, int toRoll);
void printDice(int rolledDice[], int toRoll, int *rollNumber, int heldValues[], int numberHeld);
int withholdDice(int *rolledDice, int *heldValues, int *numberHeld, int toRoll);
void arrayShrink(int *array, int size);
int areIndexLowest(int array[], int size);

// End the header file and if
#endif
