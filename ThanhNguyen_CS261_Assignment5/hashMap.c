/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Thanh Nguyen
 * Date: 11/17/17
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable: 4996)

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement

	// Create two hashlink pointers
	HashLink *cur, *prev;

	// Create a for loop to loop through the buckets
	for (int i = 0; i < map->capacity; i++)
	{
		// Create two iterators. One for the current location and one for the previous location
		cur = prev = map->table[i];

		// While this iterator does not point to null
		while (cur != 0)
		{
			cur = prev->next;		// Point current to the next link
			hashLinkDelete(prev);	// Delete prev
			prev = cur;				// Update prev to catch up to cur
		}
	}
	free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement

	// Compute the hash index
	int idx = HASH_FUNCTION(key) % map->capacity;
	
	// If the index hashes to less than 0, add the hash table's capacity to it
	if (idx < 0) 
		idx += map->capacity;

	// Go to the head of the index
	HashLink *cur = map->table[idx];

	// If that index's bucket is empty, return NULL
	if (cur == 0)
		return NULL;

	// While current has not reached the end of the linked list
	while (cur != 0)
	{
		// If a link with a matching key is found
		if (strcmp(cur->key, key) == 0)
		{
			// Return the address of the value
			return &(cur->value);
		}

		// Iterate forward
		cur = cur->next;
	}

	// End of linked list was reached and matching key was not found. Return NULL
	return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement

	// Create a variable to hold the current (old) capacity
	int oldCap = capacity / 2;

	// Create two hashlink variables to current the current and prev location of the linked list
	HashLink *cur;

	// Create a new hashmap with double the capacity
	HashMap mapDoub;
		
	hashMapInit(&mapDoub, capacity);

	// Iterate through all of the buckets of the current (old) hashmap
	for (int i = 0; i < oldCap; i++)
	{
		// Set cur to the head of the bucket
		cur = map->table[i];

		// While cur has not reached the end of the bucket
		while (cur != 0)
		{
			// Compute the hash index for the new hashmap using cur's key
			int idx = HASH_FUNCTION(cur->key) % map->capacity;

			// If the index hashes to less than 0, add the hash table's capacity to it
			if (idx < 0)
				idx += map->capacity;

			// Add values of the old hashmap to the new hashmap
			hashMapPut(&mapDoub, cur->key, cur->value);

			// Iterate current forward
			cur = cur->next;
		}
	}
	// Free the old table
	hashMapCleanUp(map);

	// Point the old table to the new table
	*map = mapDoub;
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement

	if (hashMapTableLoad(map) > MAX_TABLE_LOAD)
		resizeTable(map, map->capacity * 2);

	// Compute the hash index
	int idx = HASH_FUNCTION(key) % map->capacity;

	// If the index hashes to less than 0, add the hash table's capacity to it
	if (idx < 0)
		idx += map->capacity;

	// Create hashlink variables to loop through the linked list and to help remove links
	HashLink *cur;

	// If the hash map contains the value that we're looking for
	if (hashMapContainsKey(map, key))
	{
		// Set cur to the computed hash index
		cur = map->table[idx];

		// While cur has not reached the end of the linked list
		while (cur != 0)
		{
			// If we find a link with a matching key
			if (strcmp(cur->key, key) == 0)
			{
				// Update the link's value with the newly provided value and exit the function
				cur->value = value;
				return;
			}

			// Iterate current
			cur = cur->next;
		}
	}
	// Else, the hashmap does not contain the value that we're looking for
	else
	{	
		map->table[idx] = hashLinkNew(key, value, map->table[idx]);	// Add a new link to the bucket

		// Increase the size of the table
		map->size++;
	}
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
	
	// Make sure the table is not empty
	assert(map->size != 0);

	// Compute the hash index
	int idx = HASH_FUNCTION(key) % map->capacity;

	// If the index hashes to less than 0, add the hash table's capacity to it
	if (idx < 0)
		idx += map->capacity;

	// Create hashlink variables to loop through the linked list and to help remove links
	HashLink *cur, *prev;

	// If the hash map contains the value that we're looking for
	if (hashMapContainsKey(map, key))
	{
		// Set cur and prev to the computed hash index
		cur = prev = map->table[idx];

		// While cur has not reached the end of the linked list
		while (cur != 0)
		{
			// If we find a link with a matching key
			if (strcmp(cur->key, key) == 0)
			{
				// Special case. If the link with the matching key is at the head of the linked list
				if (cur == map->table[idx])
					map->table[idx] = cur->next;	// Point the head to the second link
				else
					prev->next = cur->next;			// Else, link the previous node to the node after current

				hashLinkDelete(cur);				// Delete the current link
				cur = 0;							// Set cur to NULL to exit loop 

				// Decrease the size of the table by 1
				map->size--;
			}
			// Else, a matching value was not found
			else
			{
				prev = cur;			// Catch up previous to current
				cur = cur->next;	// Move current forward
			}
		}
	}
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement

	// Compute the hash index
	int idx = HASH_FUNCTION(key) % map->capacity;

	// If the index hashes to less than 0, add the hash table's capacity to it
	if (idx < 0)
		idx += map->capacity;

	// Go to the head of the index
	HashLink *cur = map->table[idx];

	// If that index's bucket is empty, return not found (0)
	if (cur == 0)
		return 0;

	// While current has not reached the end of the linked list
	while (cur != 0)
	{
		// If a link with a matching key is found
		if (strcmp(cur->key, key) == 0)
		{
			// Return found (1)
			return 1;
		}

		// Iterate forward
		cur = cur->next;
	}

	// End of linked list was reached and matching key was not found. Return not found (0)
	return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement

	// Create counter variable to count number of empty buckets
	int ctr = 0;

	// Create a for loop to go through each head of the bucke
	for (int i = ctr; i < map->capacity; i++)
	{
		// If the head of the bucket points to NULL, iterate the counter variable
		if (map->table[i] == 0)
			ctr = ctr + 1;
	}

	// Return the number of empty buckets
    return ctr;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    return ((map->size)/(double)(map->capacity));
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}