#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this

	// Create the front sentinel and set its NULL
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->frontSentinel->prev = 0;

	// Create the back sentinel and set its NULL
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->backSentinel != 0);
	list->backSentinel->next = 0;

	// Point the sentinels to themselves
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;

	// Allocate the list's size to 0
	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this

	// Create the link and set its value
	struct Link * newLink = malloc(sizeof(struct Link));
	assert(newLink != 0);
	newLink->value = value;

	// Configure newLink's prev and next
	newLink->next = link;
	newLink->prev = link->prev;

	// Re-configure link's prev AND the previous link's next
	link->prev->next = newLink;
	link->prev = newLink;

	// Increment the size
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
	
	// Reset the prev and next of the links surrounding link
	link->next->prev = link->prev;
	link->prev->next = link->next;

	// Free tmp
	free(link);

	// Decrement the size
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	
	// Call addLinkBefore and pass address of whatever is in front of frontSentinel
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	// Call addLinkBefore and pass address of backSentinel
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this

	// Assert that the list isn't empty before calling this
	assert(!linkedListIsEmpty(list));

	// Return the link after the frontSentinel's value
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this

	// Assert that the list isn't empty before calling this
	assert(!linkedListIsEmpty(list));

	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this

	// Assert that the list isn't empty before calling this
	assert(!linkedListIsEmpty(list));

	// Call removeLink and pass address of the link after the frontSentinel
	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this

	// Assert that the list isn't empty before calling this
	assert(!linkedListIsEmpty(list));

	// Call removeLink and pass address of the link before the backSentinel
	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this

	if (list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this

	// Make sure the linkedList isn't empty
	assert(!linkedListIsEmpty(list));

	// Create an iterator to go through the Linked List
	struct Link * itr = list->frontSentinel->next;

	// While the iterator hasn't reached the backSentinel, print values of each link
	while (itr != list->backSentinel)
	{
		printf("%i\n", itr->value);
		itr = itr->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	// Add to the back

	// Call addLinkBefore and pass address of backSentinel
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	// Make sure the linkedList isn't empty
	assert(!linkedListIsEmpty(list));

	// Create an iterator to go through the Linked List
	struct Link * itr = list->frontSentinel->next;

	// While the iterator hasn't reached the backSentinel, check to see if the value is in the bag
	while (itr != list->backSentinel)
	{
		if (itr->value == value)
		{
			return 1;
		}
		itr = itr->next;
	}
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	// Make sure the linkedList isn't empty
	assert(!linkedListIsEmpty(list));

	// Create an iterator to go through the Linked List
	struct Link * itr = list->frontSentinel->next;

	// While the iterator hasn't reached the backSentinel, check to see if the value is in the bag
	while (itr != list->backSentinel)
	{
		if (itr->value == value)
		{
			removeLink(list, itr);
			return;
		}
		itr = itr->next;
	}
	return;
}
