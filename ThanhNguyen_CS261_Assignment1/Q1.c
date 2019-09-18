/* CS261- Assignment 1 - Q.1*/
/* Name: Thanh Nguyen
 * Date: 9/30/17
 * Solution description: Practice with structs and allocating memory for structs/pointers
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
    /*Allocate memory for ten students*/
	struct student *roster = malloc(10 * sizeof(struct student));

    /*return the pointer*/
	return roster;

}

void generate(struct student* students){
    /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	int score;
	
	/*For loop to generate IDs 1-10 for students and randomly generate test score for each student*/
	for (int i = 0; i < 10; i++)
	{
		score = rand() % 101;
		students[i].id = i + 1;
		students[i].score = score;
	}

	/*Variables to use for shuffling student IDs with Fisher Yates algorithm*/
	int x, y, tmp;

	/*Fisher Yates Shuffle. Iterate backwards through struct and generate random numbers between 0-9 to shuffle ID positions.*/
	for (int x = 9; x >= 0; x--)
	{
		y = rand() % 10;

		/*Swap*/
		tmp = students[y].id;
		students[y].id = students[x].id;
		students[x].id = tmp;
	}


}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	printf("ID  Score\n");
	for (int i = 0; i < 10; i++)
	{
		/*For student with ID of 10. Output one less space for correct formatting*/
		if (students[i].id == 10)
		{
			printf("%i  %i\n", students[i].id, students[i].score);
		}
		/*Print student IDs next to scores*/
		else
		{
			printf("%i   %i\n", students[i].id, students[i].score);
		}
	}

}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/

	/*Find the minimum and print*/
	int min = students[0].score;		// Initialize the min variable to the first score
	for (int i = 0; i < 10; i++)		// Iterate through struct to see if this min value is greater than other scores
	{
		if (min > students[i].score)
		{
			min = students[i].score;
		}
	}
	printf("The minimum score is: %i\n", min);

	/*Find the maximum and print*/
	int max = students[0].score;		// Initialize the max variable to the first score
	for (int j = 0; j < 10; j++)		// Iterate through struct to see if this max value is less than other scores
	{
		if (max < students[j].score)
		{
			max = students[j].score;
		}
	}
	printf("The maximum score is: %i\n", max);

	/*Find the average and print*/
	int sum = 0;
	for (int k = 0; k < 10; k++)		// Iterate through struct scores and sum up all scores
	{
		sum += students[0].score;
	}
	double average = sum / 10.0;
	printf("The average score is: %lf\n", average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	if (stud)
	{
		free(stud);
	}
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
	stud = allocate();
    
    /*call generate*/
	generate(stud);
    
    /*call output*/
	output(stud);
    
    /*call summary*/
	summary(stud);
    
    /*call deallocate*/
	deallocate(stud);

    return 0;
}
