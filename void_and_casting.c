#include <stdio.h>
#include <stdlib.h>

/*****************
 * the void type *
 * **************/

/* The void keyword is used primarily for three things:
 *
 * 1. as the return type of a function, where void means nothing returned,
 * 2. in a function declaration to indicate that it takes no parameters,
 * 3. as a type for pointers that means "no specific type".
 *
 * You've already seen the first two of these, so this tutorial will talk about
 * void as a type for pointers.
 *
 * A "void pointer" points to an address just like any other pointer. However,
 * it does not have a specific type, like char, integer, or float. Some
 * functions return void pointers, because the function itself can't know what
 * type the pointer is. In essence, you can think of a 'void pointer' as a
 * pointer without a type. This type of pointer functions as a character or
 * byte array, i.e., it indexes by one byte at a time.
 *
 * The most common place you'll run into void pointers is probably from
 * malloc() calls; malloc(n) returns a void pointer to a range of n bytes, or
 * NULL if the malloc() failed.
 *
 * To use a void pointer, you generally need to "cast" the void pointer to a
 * different type, which is the next thing we'll discuss.
 */

/**********************************
 * type-casting -- or just casting *
 * ********************************/

/* Casting is how you tell the compiler that you want to change the type of a
 * certain variable from one type to another. There are a variety of reasons
 * why you might want to do this. Perhaps the most essential reason to cast
 * something is when you cast the void pointer returned by a malloc() call to
 * whatever type you need the allocation to be (e.g., int, float, or char).
 *
 * We will demonstrate a variety of casts below.
 */

int main(int argc, char *argv[]) {

	void *x; /* a void pointer on the stack */

	x = malloc(1024); /* malloc 1024 bytes -- x is still void */

	if (x == NULL) {
		printf("%s:%d - Malloc failed!\n", __FILE__, __LINE__);
		return 1;
	}

	/* x is a void pointer to 1024 bytes of memory. */

	// x[0] = 123; // I'm not allowed to do this, because it's void!
	
	/* Before I can use (i.e., dereference) a void pointer, I need to cast it
	 * to something else. */

	int *intptr;
	intptr = (int *)x; /* cast x to be a pointer to an int, and assign it to
						  intptr. Now I can use it for ints! */
	intptr[0] = 10;
	printf("I put %d into intptr[0]!\n", intptr[0]);

	/*****************************************
	 * if you malloc() don't forget to free! *
	 * **************************************/

	/* I'm done with x now, so I need to free it. To free a heap pointer, call
	 * free on the pointer (the original address of the allocation. */

	free(intptr); // could also have done free(x)

	/********************************
	 * a cleaner malloc() syntax... *
	 * *****************************/

	/* We don't usually go through all those steps when we call malloc. We
	 * often declare a variable, call malloc, and cast the result in one step. 
	 *
	 * We also don't normally malloc() a raw number of bytes, but the multiple
	 * of the size of whatever we want to put in the buffer.
	 *
	 * I'll demonstrate both below:
	 */

	int *ten_ints = (int *)malloc(sizeof(int) * 10);

	/* remember to check to see if the malloc succeeded: */
	if (ten_ints == NULL) {
		printf("%s:%d - Malloc failed!\n", __FILE__, __LINE__);
		return 1;
	}

	int i;
	printf("\nFill and print array...\n");
	for (i = 0; i < 10; i++) {
		ten_ints[i] = i;
		printf("Integer %d is %d...\n", i, i);
	}


	/********************
	 * free()ing memory *
	 * *****************/

	/* ok, we're done with ten_ints, let's free it! */

	free(ten_ints);

	/*************************
	 * use after free (BAD!) *
	 * **********************/

	printf("\nUsing ten_ints after free() :scream_emoji:\n");
	for (i = 0; i < 10; i++) {
		printf("Integer %d is %d...\n", i, i);
	}

	/* The data for ten_ints hasn't been changed, because nothing else has
	 * reused that memory. But using a pointer after it has been free()d is a
	 * BIG nono, because you told the program that you were done with it.
	 * Anything in your process could use that memory, or the OS could have
	 * identified that memory as no longer in use, which could cause a crash if
	 * you access it.
	 */

	/************************
	 * other types of casts *
	 * *********************/

	/* Sometimes, you might cast a larger data type to a smaller data type to interact with it in a different way. For example, by casting an int to a character array, I can change the number by manipulating the character array.
	 */

	int integer = 1000;
	printf("integer holds: %d\n", integer);
	
	/* now let's mess with the bytes of that integer */
	unsigned char *intbytes = (unsigned char *)&integer; /* using the address of integer as a char pointer */

	unsigned int bytes_in_int = sizeof(int); /* probably 4, but just making sure */
	
	for (i = 0; i < bytes_in_int; i++) {
		/* \t in a printf is a tab character */
		printf("byte %d - char: '%c'\tdecimal: %d\thex: %02x\n", i, intbytes[i], intbytes[i], intbytes[i]);
	}

	/* let's mess with the integer */
	intbytes[0] = 0;
	intbytes[1] = 0;
	intbytes[2] = 0;
	intbytes[3] = 1;

	/* now let's see what happened to the int after we messed with it: */
	printf("integer holds: %d (hex: %08x)\n", integer, integer);
	for (i = 0; i < bytes_in_int; i++) {
		/* \t in a printf is a tab character */
		printf("byte %d - char: '%c'\tdecimal: %d\thex: %02x\n", i, intbytes[i], intbytes[i], intbytes[i]);
	}

	/* we used casting to allow us to access the four bytes of an integer as a
	 * character array. Then, we changed the bytes in the integer, and then we
	 * looked at the integer in integer form and saw that the value was greatly
	 * changed.
	 *
	 * These kind of things aren't super useful in a day to day sense, unless
	 * you are doing data maniupation.
	 */


	
	return 0;

}
