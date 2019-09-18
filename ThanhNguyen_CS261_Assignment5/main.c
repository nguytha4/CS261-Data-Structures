#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

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
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---

	// Create a file object that will be read from
	FILE * output_file = fopen(fileName, "r");

	// Create a char pointer to hold the words that will be read from the nextWord function
	char * curWord = nextWord(output_file);

	// While there are still words in the text file
	while (curWord != NULL)
	{
		// If the hashmap already has the word
		if (hashMapContainsKey(map, curWord))
		{
			int * val = hashMapGet(map, curWord);	// Get the pointer to the current value of the word
			*val = *val + 1;						// Dereference the val and increment it
		}
		// Else, the value is not in the hashmap
		else
		{
			hashMapPut(map, curWord, 1);			// Add the new word onto the hashmap with a value of 1
		}
		free(curWord);								// Free the current word
		curWord = nextWord(output_file);			// Set the current word to the next word in the text file
	}

	fclose(output_file);							// Close the file object

	// Print each word and its occurrences
	printf("\n");

	for (int i = 0; i < map->capacity; i++)
	{
		HashLink* link = map->table[i];
		while (link != NULL)
		{
			printf("%s:  %i\n", link->key, link->value);
			link = link->next;
		}
	}

    // Be sure to free the word after you are done with it here.
    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}