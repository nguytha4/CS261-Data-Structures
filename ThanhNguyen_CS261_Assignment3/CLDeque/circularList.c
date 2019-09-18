#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this

	// Create a sentinel and allocate space for it
	list->sentinel = malloc(sizeof(struct Link));

	// Configure the sentinel's prev and next pointers to itself
	list->sentinel->prev = list->sentinel;
	list->sentinel->next = list->sentinel;

	// Allocate the size to size
	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this

	// Create a new link and allocate memory for it
	struct Link * newLink = malloc(sizeof(struct Link));
	
	// Set the new link's value
	newLink->value = value;

	// Set the new link's prev and next pointers to null
	newLink->prev = newLink->next = 0;

	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this

	// Call createLink to create a newLink with pointers that need to be set
	struct Link * newLink = createLink(value);

	// Set newLink's pointers
	newLink->prev = link;
	newLink->next = link->next;

	// Reset the links that newLink is being inserted between
	link->next->prev = newLink;
	link->next = newLink;

	// Increase the list's size
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this

	// Reset the pointers pointing to the link to be removed
	link->prev->next = link->next;
	link->next->prev = link->prev;

	// Free the link to be removed
	free(link);

	// Decrement the list's size
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this

	while (!circularListIsEmpty(list))
	{
		circularListRemoveFront(list);
	}
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this

	// If this is the first value being added
	if (circularListIsEmpty(list))
	{
		addLinkAfter(list, list->sentinel, value);
		list->sentinel->prev = list->sentinel->next;	// Special case where we must manually configure sentinel's prev
	}
	else
	{
		addLinkAfter(list, list->sentinel, value);
	}
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this

	// If this is the first value being added
	if (circularListIsEmpty(list))
	{
		addLinkAfter(list, list->sentinel->prev, value);
		list->sentinel->prev = list->sentinel->next;	// Special case where we must manually configure sentinel's prev
	}
	else
	{
		addLinkAfter(list, list->sentinel->prev, value);
	}
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// Make sure the deque is not empty
	assert(!circularListIsEmpty(list));

	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// Make sure the deque is not empty
	assert(!circularListIsEmpty(list));
	
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this

	// Make sure the deque is not empty
	assert(!circularListIsEmpty(list));

	// Special case, if the size equals to 1
	if (list->size == 1)
	{
		struct Link * tmp = list->sentinel->next;
		list->sentinel->prev = list->sentinel->next = list->sentinel;	// Reset the sentinel prev and next to point to itself
		free(tmp);
		list->size--;
	}
	else
	{
		removeLink(list, list->sentinel->next);
	}
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this

	// Make sure the deque is not empty
	assert(!circularListIsEmpty(list));

	// Special case, if the size equals to 1
	if (list->size == 1)
	{
		struct Link * tmp = list->sentinel->prev;
		list->sentinel->prev = list->sentinel->next = list->sentinel;	// Reset the sentinel prev and next to point to itself
		free(tmp);
		list->size--;
	}
	else
	{
		removeLink(list, list->sentinel->prev);
	}
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	if (list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this

	// Make sure the deque is not empty
	assert(!circularListIsEmpty(list));

	// Create an iterator to go through the Linked List
	struct Link * itr = list->sentinel->next;

	// While the iterator hasn't reached the sentinel, print values of each link
	while (itr != list->sentinel)
	{
		printf("%lf\n", itr->value);
		itr = itr->next;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this

	// Make sure the deque is not empty
	assert(!circularListIsEmpty(list));

	struct Link * lead = list->sentinel;
	struct Link * follow = list->sentinel->prev;

	do
	{
		lead->prev = lead->next;	// Switch the current link's previous to point to next's direction
		lead->next = follow;		// Switch the current link's next to point to where follow is waiting

		// Update follow to catch up with lead
		follow = lead;

		// Move lead forward
		lead = lead->prev;

	} while (lead != list->sentinel);
}
