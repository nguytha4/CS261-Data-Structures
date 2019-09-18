/* CS261- Assignment 1 - Q.5*/
/* Name: Thanh Nguyen
 * Date: 9/30/17
 * Solution description: Take word entered by user and convert it to "sticky case"
 */
 
#include <stdio.h>
#include <stdlib.h>
#pragma warning( disable : 4996)

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/

	/*If the letter being checked is an even index, check if it is lowercase to convert to uppercase*/
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (i % 2 == 0)
		{
			if (word[i] < 'A' || word[i] > 'Z')
			{
				word[i] = toUpperCase(word[i]);
			}
		}
		/*Else, the letter being checked is an odd index and needs to be checked for uppercase to convert to lowercase*/
		else
		{
			if (word[i] >= 'A' && word[i] <= 'Z')
			{
				word[i] = toLowerCase(word[i]);
			}
		}
	}

}

int main(){
	/*Allocate a char array of 50 characters*/
	int size = 50;
	char *word = malloc(size * sizeof(word));
	
	/*Read word from the keyboard using scanf*/
	printf("Please enter a word: ");
	scanf("%s", word);

    /*Call sticky*/
	sticky(word);
    
    /*Print the new word*/
	printf("Sticky caps: %s\n", word);

	/*Deallocate the char array if the pointer is not NULL*/
	if (word)
	{
		free(word);
	}

    return 0;
}
