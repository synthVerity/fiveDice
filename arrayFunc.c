// Use the custom header file
#include "arrayFunc.h"

// Function to make all values in an array be at the lowest point possible
void arrayShrink(int *array, int size)
{
	// Function variables
	int i;
	int fractured = areIndexLowest(array, size);

	printf("%d\n", size);

	// Loop to keep function going until job is complete
	while(fractured)
	{
		// Loop to travel through array for empty spaces
		for(i = size; i > 0; i--)
		{
			// Find empty spaces that have values to transfer
			if(array[i-1] == 0 && array[i] != 0)
			{
				// Replace the value of the empty space and set it to zero
				array[i-1] = array[i];
				array[i] = 0;
			}
		}

		// Check to see if the job is complete
		fractured = areIndexLowest(array, size);
	}

	return;
}

// Function to make sure array is using lowest possible indexes
int areIndexLowest(int array[], int size)
{
	// Function variables
	int i;

	// Actual loop to do the checking
	for(i = size; i >= 0; i--)
	{
		// Find stray values in higher indexes
		if(array[i] != 0 && array[i-1] == 0)
		{
			// Return value to continue work
			return 1;
		}
	}

	// Return value that work is done
	return 0;
}
