#include <stdio.h>

int main(int argc, char *argv[]) {

	/************
	 * pointers *
	 ***********/
	 
	/* A pointer is a special type of variable with two modes of use,
	 * 1) a memory location (i.e., 'reference') or 2) the contents of that 
	 * memory (this second mode is often called 'dereferencing').
	 *
	 * 1) Memory location is its default mode. You can assign a value to it
	 * like you would a regular variable, pointer variable then "holds" 
	 * the memory address you assigned (addresses are just numbers).
	 * 
	 * 2) When dereferencing the pointer, you get whatever is *in* that 
	 * memory address when you dereference it.
	 *
	 * HOW DO I GET ADDRESSES OF THINGS TO USE WITH POINTERS?
	 * 
	 * Often, a pointer will be given to you already with a memory address
	 * in it. Other times, you need to assign the pointer to the address 
	 * the variable you want the pointer to point *to*.
	 * To get the address corresponding to a variable, you can use the
	 * ampersand (&) operator. If 'x' is variable, then '&x' is the 
	 * address of the memory that x is using.
	 */

	/* you already know how to declare and set the value of an int */
  	int x = 4096;
  	int y = 1024;
	  
	/* To declare a pointer, use an asterisk: */
	int *intpointer; 

	/* let's print the value of intpointer: */
	printf("intpointer currently points at address: %p\n", intpointer);

	/* notice the *p symbol -- this is a memory address! */
	  
	/* let's point intpointer at x */
	intpointer = &x; // intpointer now points at the address of x
	  
	/* let's print x, y, *intpointer, and intpointer */
	printf("x: %d, y: %d, *intpointer: %d, intpointer: %p\n", x, y,
		*intpointer, intpointer);
	  
	/* what happens to the pointer if we change x? */
	x = 4097;
	printf("x: %d, y: %d, *intpointer: %d, intpointer: %p\n", x, y,
		*intpointer, intpointer);

	/* notice the address of the pointer does not change, but the contents of
	 * *inpointer follows the contents of whatever it points to. It is not a
	 * copy, it's a reference to the same thing! */
	  
	/* what if we change the value of *intpointer instead? */
	*intpointer = 4098;
	  
	/* looks like we can change x or *intpointer ! */
	printf("x: %d, y: %d, *intpointer: %d, intpointer: %p\n", x, y,
		*intpointer, intpointer);
	  	
	/* what if we point intpointer at &y instead of &x ? */
	intpointer = &y; // notice no * but we use & with the variable
	printf("x: %d, y: %d, *intpointer: %d, intpointer: %p\n", x, y,
		*intpointer, intpointer);

	/* Notice that the address of intpointer changed! */
	  
	/* what if we change y? */
	y = 1001;
	printf("x: %d, y: %d, *intpointer: %d, intpointer: %p\n", x, y,
	  	*intpointer, intpointer);
	  	
	/* what if we change *intpointer now? */
	*intpointer = 1002;
	printf("x: %d, y: %d, *intpointer: %d, intpointer: %p\n", x, y,
	  	*intpointer, intpointer);	  

	/* so, whichever variable's address is being pointed to by intpointer can
	 * be changed by dereferencing intpointer! */

	/*******************************
	 * pointers of different types *
	 * ****************************/

	/* everything we did above was with int pointers. But we can make and use
	 * pointers to any types we want. E.g.: */

	char c = 'c';
	char *cptr = &c;
	float f = 3.14;
	float *fptr = &f;

	/* ^--- is how you declare and point a pointer in one step. 
	 *
	 * Below, we print a couple different variables and pointers to those
	 * variables (it all should work as expected)
	 * */

	printf("c: %d, cptr: %d, f: %f, fptr: %f\n", c, *cptr, f, *fptr);


	/* Finally, pointers themselves have addresses, and you can print them if
	 * you want. */

	printf("intpointer currently points at address: %p\n", intpointer);
	printf("The address of intpointer itself is: %p\n", &intpointer);

	/* You probably won't need to use this feature, though, unless you start
	 * doing pointers to pointers, and that's way beyond the scope of this
	 * tutorial. */

	return 0;

}
