/* CS261- Assignment 1 - Q.4*/
/* Name: Thanh Nguyen
 * Date: 9/30/17
 * Solution description: Sort a struct of students with unique IDs from 1-10 by their scores in ascending order
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/     

	int min = 0;	// Variable to hold the current minimum value
	int tmp;		// Variable to use to swap
	int mindex = 0;	// Variable to hold the index of the minimum value

	/*Use selection sort to sort the struct in ascending order by scores*/
	for (int i = 0; i < n; i++)
	{
		min = students[i].score;

		mindex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (min > students[j].score)
			{
				min = students[j].score;
				mindex = j;
			}
		}

		if (mindex != i)
		{
			tmp = students[mindex].score;
			students[mindex].score = students[i].score;
			students[i].score = tmp;

			tmp = students[mindex].id;
			students[mindex].id = students[i].id;
			students[i].id = tmp;
		}

	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
	int n = 10;
    
    /*Allocate memory for n students using malloc.*/
	struct student *roster = malloc(n * sizeof(struct student));
    
    /*Generate random and unique IDs and random scores for the n students, using rand().*/
	for (int i = 0; i < n; i++)
	{
		roster[i].id = i+1;
		roster[i].score = rand();
	}

	/*Variables to use for shuffling student IDs with Fisher Yates algorithm*/
	int x, y, tmp;

	/*Fisher Yates Shuffle. Iterate backwards through struct and generate random numbers between 0-9 to shuffle ID positions.*/
	for (int x = 9; x >= 0; x--)
	{
		y = rand() % 10;

		/*Swap*/
		tmp = roster[y].id;
		roster[y].id = roster[x].id;
		roster[x].id = tmp;
	}
    
    /*Print the contents of the array of n students.*/
	printf("ID  Score (unsorted)\n");
	for (int j = 0; j < n; j++)
	{
		if (roster[j].id == 10)
		{
			printf("%i  %i\n", roster[j].id, roster[j].score);
		}
		else
		{
			printf("%i   %i\n", roster[j].id, roster[j].score);
		}
	}

    /*Pass this array along with n to the sort() function*/
	sort(roster, n);
    
    /*Print the contents of the array of n students.*/
	printf("\nID  Score (sorted)\n");
	for (int j = 0; j < n; j++)
	{
		if (roster[j].id == 10)
		{
			printf("%i  %i\n", roster[j].id, roster[j].score);
		}
		else
		{
			printf("%i   %i\n", roster[j].id, roster[j].score);
		}
	}

	/*Deallocate memory from the struct if it is not NULL*/
	if (roster)
	{
		free(roster);
	}
    
    return 0;
}
