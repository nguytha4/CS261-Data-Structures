#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"
#pragma warning(disable:4996)


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
  	/* FIX ME */

	/* Make sure the list is not empty */
	assert(heap != 0);

	/* Create a for loop to loop through all of the items in the heap */
	for (int i = 0; i < heap->size; i++)
	{
		/* Write the priority to the file */
		fprintf(filePtr, "%d\t", heap->data[i].priority);

		/* Create a for loop to print out the task description */
		for (int j = 0; j < strlen(heap->data[i].description); j++)
		{
			fprintf(filePtr, "%c", heap->data[i].description[j]);
		}

		/* If at the end of the list, do not print a newline */
		if (i == heap->size - 1)
		{
			return;
		}
		/* Otherwise, print a newline for the next task */
		else
		{
			fprintf(filePtr, "\n");
		}
	}
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{
  	/* FIX ME */

	/* Create an integer to hold the task's priority */
	int pri;

	char * pch;		/* Char pointer to hold the split strings */
	char *nlptr;	/* Char pointer to remove the newline character */

	char myString[TASK_DESC_SIZE];		/* Char array to hold the priority and description string */

	/* Use fgets to grab each line from the text file, 100 characters at a time */
	if (fgets(myString, 100, filePtr) != 0)
	{
		/* Remove the newline character at the end */
		nlptr = strchr(myString, '\n');
		if (nlptr)
			*nlptr = '\0';
	}

	do
	{
		/* Remove the newline character at the end */
		nlptr = strchr(myString, '\n');
		if (nlptr)
			*nlptr = '\0';

		/* Parse the line in the text file to get the priority */
		pch = strtok(myString, "\t");

		/* Set the priority */
		pri = atoi(pch);

		/* Parse the next string to get the description */
		pch = strtok(NULL, "\t");

		/* Create a new task and add it to the heap */
		TYPE newTask = createTask(pri, pch);
		addHeap(heap, newTask);

	  /* Continue to get each line of the text file until the end is reached */
	} while (fgets(myString, 100, filePtr) != NULL);

}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
  	/* FIX ME  */
	
	/* Make sure the list is not empty */
	assert(heap != 0);

	/* Create a temporary array to copy into. We need this to sort without affecting the original. */
	DynArr copyHeap;

	/* Copy the current array into the newly created array */
	copyDynArr(heap, &copyHeap);

	/* Sort the copied array */
	sortHeap(&copyHeap);

	/* Print the copied/sorted array */
	for (int i = copyHeap.size-1; i >= 0; i--)
	{
		printf("%s\n\n", copyHeap.data[i].description);
	}

	/* Delete the copied/sorted array */
	freeDynArr(&copyHeap);
	
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
