/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */	

	// If no string is passed in, mark as balanced
	if (s == 0)
	{
		return 1;
	}

	// Create a stack to hold/manipulate the char variables
	DynArr *dyn;
	dyn = newDynArr(4);

	// Create a char variable to read in chars one by one
	char reader = nextChar(s);

	// Loop through the string and stop when the null character is reached
	while (reader != '\0')
	{
		// If the reader character is a left paren, push a right paren onto the stack
		if (reader == '(')
			pushDynArr(dyn, ')');
		// Else if the reader character is a left curly bracket, push a right curly bracket onto the stack
		else if (reader == '{')
			pushDynArr(dyn, '}');
		// Else if the reader character is a left bracket, push a right bracket onto the stack
		else if (reader == '[')
			pushDynArr(dyn, ']');

		// Else if the reader character is a right paren, pop a right paren off the stack if possible
		else if (reader == ')')
		{
			// If the array not empty and the top of the array is a right paren, pop off the right paren
			if (isEmptyDynArr(dyn) != 1 && topDynArr(dyn) == ')')
				popDynArr(dyn);
			// Else delete the array and mark the equation as not balanced
			else
			{
				deleteDynArr(dyn);
				return 0;
			}
		}
		// Else if the reader character is a right curly bracket, pop a right curly bracket off the stack if possible
		else if (reader == '}')
		{
			// If the array not empty and the top of the array is a right curly bracket, pop off the right curly bracket
			if (isEmptyDynArr(dyn) != 1 && topDynArr(dyn) == '}')
				popDynArr(dyn);
			// Else delete the array and mark the equation as not balanced
			else
			{
				deleteDynArr(dyn);
				return 0;
			}
		}
		// Else if the reader character is a right bracket, pop a right bracket off the stack if possible
		else if (reader == ']')
		{
			// If the array not empty and the top of the array is a right bracket, pop off the right bracket
			if (isEmptyDynArr(dyn) != 1 && topDynArr(dyn) == ']')
				popDynArr(dyn);
			// Else delet the array and mark the equation as not balanced
			else
			{
				deleteDynArr(dyn);
				return 0;
			}
		}

		// "Iterate" the char variable to check the next char
		reader = nextChar(s);
	}

	// Once the string has been iterated through, check to see if it is empty. If empty, delete the array and mark as balanced
	if (isEmptyDynArr(dyn) == 1)
	{
		deleteDynArr(dyn);
		return 1;
	}
	// Else, the array is not empty. Delete the array and mark as unbalanced
	else
	{
		deleteDynArr(dyn);
		return 0;
	}
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

