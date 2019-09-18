/* CS261- Assignment 1 - Q. 0*/
/* Name: Thanh Nguyen
 * Date: 9/28/17
 * Solution description: Variable declration, function, and pointer practice
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("The value pointed to by iptr* is: %i\n", *iptr);

     /*Print the address pointed to by iptr*/
	printf("The address pointed to by itpr* is: %p\n", iptr);

     /*Print the address of iptr itself*/
	printf("The address of iptr is: %p\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
	int x = 123;

    /*print the address of x*/
	printf("The address of x is: %p\n", &x);

    /*Call fooA() with the address of x*/
	fooA(&x);

    /*print the value of x*/
	printf("The value of x is: %i\n", x);

    return 0;
}
