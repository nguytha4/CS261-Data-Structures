/* CS261- Assignment 1 - Q.3*/
/* Name: Thanh Nguyen
 * Date: 9/30/17
 * Solution description: Practice sorting an array
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void sort(int* number, int n){
     /*Sort the given array number, of length n*/  

	int min = 0;	// Variable to hold the current minimum value
	int tmp;		// Variable to use to swap
	int mindex = 0;	// Variable to hold the index of the minimum value

	/*Use selection sort to sort the array in ascending order*/
	for (int i = 0; i < n; i++)
	{
		min = number[i];

		mindex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (min > number[j])
			{
				min = number[j];
				mindex = j;
			}
		}

		if (mindex != i)
		{
			tmp = number[mindex];
			number[mindex] = number[i];
			number[i] = tmp;
		}

	}

}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
	int* intarray = malloc(n * sizeof(intarray));
    
    /*Fill this array with random numbers, using rand().*/
	for (int i = 0; i < n; i++)
	{
		intarray[i] = rand();
	}
    
    /*Print the contents of the array.*/
	printf("Unsorted:\n");
	for (int j = 0; j < n; j++)
	{
		printf("%i\n", intarray[j]);
	}

    /*Pass this array along with n to the sort() function of part a.*/
	sort(intarray, n);
    
    /*Print the contents of the array.*/    
	printf("\nSorted:\n");
	for (int k = 0; k < n; k++)
	{
		printf("%i\n", intarray[k]);
	}

    /*Free the memory allocated to the array if it is not NULL*/
	if (intarray);
	{
		free(intarray);
	}

    return 0;
}
