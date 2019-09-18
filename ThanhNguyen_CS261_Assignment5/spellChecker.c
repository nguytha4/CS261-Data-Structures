#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

#pragma warning(disable: 4996)

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement

	// Create a char pointer to hold each word in the dictionary as its being read in
	char * curWord = nextWord(file);

	// While the end of the dictionary has not been reached yet
	while (curWord != NULL)
	{
		hashMapPut(map, curWord, 1);	// Add the word from the dictionary into the hashmap
		free(curWord);					// Free the word
		curWord = nextWord(file);		// Load the next word into the char pointer
	}
}

/*************************************************************************************************/

/*Source: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C */

int levenshtein(char *s1, char *s2) {
	unsigned int x, y, s1len, s2len;
	s1len = strlen(s1);
	s2len = strlen(s2);
	unsigned int matrix[50][50];
	matrix[0][0] = 0;
	for (x = 1; x <= s2len; x++)
		matrix[x][0] = matrix[x - 1][0] + 1;
	for (y = 1; y <= s1len; y++)
		matrix[0][y] = matrix[0][y - 1] + 1;
	for (x = 1; x <= s2len; x++)
		for (y = 1; y <= s1len; y++)
			matrix[x][y] = MIN3(matrix[x - 1][y] + 1, matrix[x][y - 1] + 1, matrix[x - 1][y - 1] + (s1[y - 1] == s2[x - 1] ? 0 : 1));

	return(matrix[s2len][s1len]);
}

/*************************************************************************************************/

/*Add LD values into dictionary compared to what user input*/
void hashMapLD(HashMap * map, char * input)
{
	int LD = 0;

	for (int i = 0; i < map->capacity; i++)
	{
		HashLink * cur = map->table[i];

		while (cur != 0)
		{
			LD = levenshtein(input, cur->key);
			hashMapPut(map, cur->key, LD);
			cur = cur->next;
		}
	}
}

/*************************************************************************************************/

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);

		if (strcmp(inputBuffer, "quit") == 0)
		{
			quit = 1;
		}

		// Implement the spell checker code here..

		// Else if the inputted word can be found in the dictionary. Let the user know.
		else if (hashMapContainsKey(map, inputBuffer))
		{
			printf("The word was spelled correctly.\n");
		}
		// Else, it's not found in the dictionary.
		else
		{
			// Add LD values into the dictionary as compared to what the user input
			hashMapLD(map, inputBuffer);

			// Create a table of words for the suggested values
			HashLink suggWords[6];

			// Initialize the value of all words in the table of words to 100 to ensure the system doesn't do any bad comparisons
			for (int i = 0; i < 6; i++)
			{
				suggWords[i].value = 100;
			}

			// Variable to hold the LD value of each word
			int * LD;

			// For loop to go through all the dictionary's buckets
			for (int j = 0; j < map->capacity; j++)
			{
				// Iterator to iterate through every bucket
				HashLink * cur = map->table[j];

				// While the iterator is not null
				while (cur != 0)
				{
					// Get the location of the current value of the current word in the dictionary
					LD = hashMapGet(map, cur->key);
					
					// Create a for loop to compare the current dictionary's value
					for (int k = 0; k < 6; k++)
					{
						// If the dictionary's value is less than any of the values in the suggested list
						if (*LD < suggWords[k].value)
						{
							// Add the current dictionary word to the suggested words table
							suggWords[k].key = cur->key;
							suggWords[k].value = cur->value;

							// Jump out of for loop
							k = 6;
						}
					}

					// Proceed the iterator forward
					cur = cur->next;
				}
			}

			// Print the suggested words
			for (int l = 0; l < 6; l++)
			{
				printf("Did you mean %s?\n", suggWords[l].key);
			}
		} 
    }
    
    hashMapDelete(map);
    return 0;
}