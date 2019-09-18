/* CS261- Assignment 1 - Q.2*/
/* Name: Thanh Nguyen
 * Date: 9/30/17
 * Solution description: Practice with pointers and passing by value/reference
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = (*a)*2;

    /*Set b to half its original value*/
	*b = (*b) / 2;

    /*Assign a+b to c*/
	c = (*a) + (*b);

    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;

    /*Print the values of x, y and z*/
	printf("The value of x is: %i\n", x);
	printf("The value of y is: %i\n", y);
	printf("The value of z is: %i\n", z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
	int fooint = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
	printf("The value returned by foo is: %i\n", fooint);

    /*Print the values of x, y and z again*/
	printf("The value of x is: %i\n", x);
	printf("The value of y is: %i\n", y);
	printf("The value of z is: %i\n", z);
 
    /*Is the return value different than the value of z?  Why?*/
	// The return value of z did not change because of two reasons:
	// 1) It was passed by value into the function foo so any changes to it only affect its copied value. The original variable retains its original value.
	// 2) No changes were made to z in foo so even if it was passed by reference into this function, it still would have remained a value of 7.

    return 0;
}
    
    
