#include <stdio.h>

/* code for this function at the end of the file */
void print_ints(int *array, unsigned int num);

int main(int argc, char *argv[]) {

	/**********
	 * arrays *
	 * *******/

	/* HOW DO C ARRAYS WORK? 
	 *
	 * Arrays in C work pretty similarly to arrays in other languages -- at
	 * at least in the most fundamental way: you can index into them to read or
	 * set values.
	 *
	 * HOW DON'T C ARRAYS WORK?
	 *
	 * C Arrays are not objects, full stop. As a result, they do not have
	 * built-in methods of any kind to let you splice them, sort them, get
	 * their length, etc. You can't make them longer just by adding more
	 * elements to them or increasing their index.  You *can* do all those
	 * things, of course, but doing so will require code, other variables,
	 * other data structures, or by making a new array and copying the elements
	 * over. C arrays are a no-frills economy-class data structure.
	 *
	 * REMEMBER: C IS STRONGLY TYPED
	 *
	 * Additionally, remember that C is strongly typed. This means that
	 * elements in an array must be the same type as the array type (i.e., int,
	 * char, float, etc.). For example, you can't put a float into an int array
	 * without doing something called 'cast'ing.  (If we discuss casting, it
	 * will be in a later lesson.)
	 *
	 * INTERNALS (IMPORTANT!)
	 *
	 * Internally (i.e., "in reality"), an array is a pointer to a contiguous
	 * region of memory (i.e., all next to each other) that contains n elements
	 * of a particular type (e.g., char, int, float, etc.) -- one after the
	 * other in address order.
	 *
	 * Array access / bracket notation (e.g., array[n]) tells the C compiler to
	 * get the nth element of the given type from the array -- in other words,
	 * 'array[n]' notation dereferences memory at the nth slot past the address
	 * in the pointer (the address pointed to by 'array') -- where each slot is
	 * the size of the data type. For example, array[4] says get the 5th thing
	 * from the start of the array (which is the location pointed to by the
	 * pointer 'array').
	 *
	 * RECAP
	 *
	 * The main difference between, say, a C array of ints and a Python array
	 * of ints, is that the Python array is an object that includes the
	 * elements, the number of elements as a property, and other metadata in
	 * addition to methods that operate on the array object. In C, the compiler
	 * just sets up space for n items of type t and points to the first item in
	 * the list.  So, in C it's easy to go over the end of the array...  this
	 * is called an array or buffer overflow, but that's a subject for a later
	 * date (or maybe another class!).
	 */

	/* empty arrays of a certain type and size are declared like this */
	
	int intarray[10];       // this can hold an array of 10 ints
	char chararray[10];     // this holds an array of 10 chars
	float floatarray[10];   // this holds an array of 10 floats

	/* you can assign and the array as you would expect */

	intarray[0] = 0;
	floatarray[0] = 3.14;
	chararray[0] = 'A';
	
	/* you can print the array as you would expect */
	
	printf("intarray[0] = %d\n", intarray[0]);
	printf("floatarray[0] = %f\n", floatarray[0]);
	printf("chararray[0] = %c\n", chararray[0]);
	
	/* we can assign the values using loops if we want */
	
	int i = 0;
	
	for (i = 0; i < 10; i++ ) {
		/* assign all values of intarray and print them by index */
		intarray[i] = i;
		printf("intarray[%d] = %d\n", i, intarray[i]);
	}

	// fill the array with multiples of pi
	for (i = 0; i < 10; i++ ) {
		floatarray[i] = floatarray[0] * (i + 1);
		printf("floatarray[%d] = %0.2f\n", i, floatarray[i]);
	}

	// fill the array with the next 9 characters
	for (i = 0; i < 10; i++ ) {
		chararray[i] = chararray[0] + i; // double pi by index
		printf("chararray[%d] = %c\n", i, chararray[i]);
	}

	/**********************
	 * POINTER ARITHMETIC *
	 * ********************/

	/* Remember that arrays in C are just pointers. As a result, in addition to
	 * bracket notation (e.g., array[n]) we can access array members by
	 * calculating the address of the item we want and dereferencing it like a
	 * pointer. This is commonly called "pointer arithmetic." Sometimes -- but
	 * rarely -- this is the best way to access an array. We're showing this
	 * too you so that you'll know what it is when you see it.
	 *
	 * I can get the first character in chararray in the classic way:
	 */

	printf("the 0th element of chararray is: %c\n", chararray[0]);
	 
	/* ...but I can also get it by computing the address and dereferencing: */

	printf("the 0th element of chararray is: %c\n", *(chararray + 0));
	 
	/* ...of course, adding 0 is the same as the following */

	printf("the 0th element of chararray is: %c\n", *chararray);

	/* ALL THREE of these methods are ways to say "give me the 0th character
	 * starting at the pointer 'chararray'". 
	 *
	 * It follows then that the following are also equivalent: */
	
	printf("the 1st element of chararray is: %c\n", chararray[1]);
	printf("the 1st element of chararray is: %c\n", *(chararray + 1));

	/* This one works because we are adding one to the address pointed to
	 * by 'chararray' and then dereferencing it, which is the next byte in
	 * memory.
	 *
	 * This also works with other types that have larger sizes (e.g., ints and
	 * floats) because the compiler knows the size of each type, so it
	 * automatically multiplies the number in the arithmetic with the size of
	 * the data type to compute the proper address of the array item you are
	 * requesting.
	 */

	printf("floatarray[7] is %f\n", floatarray[7]);
	printf("*(floatarray + 7) is %f\n", *(floatarray + 7));

	printf("intarray[5] is %d\n", intarray[5]);
	printf("*(intarray + 5) is %d\n", *(intarray + 5));

	/* Remember, in general, it is better to use array[n] notation. */

	/******************************************
	 * Passing arrays as a function parameter *
	 * ****************************************/

	/* When you want to pass an array to a function, you pass the pointer to
	 * the array. This allows the function to modify the data in the array,
	 * since the pointer gives the function the memory address pointing to the
	 * start of the array data. Since arrays do not include any length
	 * information (or anything else!), you also need to communicate to the
	 * function the length of the array in some way, such as by passing an
	 * unsigned integer, or by including a "stop" value in the array (risky).
	 *
	 * This function prints n ints from an array pointer in a comma-separated
	 * form. (The code for print_ints is at the bottom of this file.)
	 */

	print_ints(intarray, 10);

	/*************************
	 * CRIMES AGAINST ARRAYS *
	 * **********************/
	
	/* C array notations will let you do bad things, because arrays are just
	 * pointers. */

	/* Here's something bad that you can do: */

	printf("this is bad: chararray[-1] = %c\n", chararray[-1]);

	/* Why is this bad? Think about it for a second...
	 *
	 *
	 *
	 * 'chararray' points to the first item in the array, so chararray[0]
	 * returns the first item. chararray[1] returns the next item, etc. That
	 * means that chararray[-1] returns the byte of memory *before* the start
	 * of chararray! And we don't know what that is!
	 *
	 * Unlike some languages, where negative indexes start from the end of the
	 * array and work backwards, in C, negative array indexes cause you to
	 * calculate the address *before* the pointer and just start reading
	 * whatever process memory happens to be there. Try running this program
	 * multiple times... you'll see that the value printed here changes with
	 * runs, presumably because it is part of a randomized or unspecified
	 * value! Yikes! Reading a deterministic variable and getting "random"
	 * values back should creep you out! Welcome to Bug City!
	 */

	/* Here's another bad thing you can do: */
	floatarray[11] = 123456.789;

	/* Why is this bad? Think about it for a second...
	 *
	 *
	 *
	 *
	 *
	 * There is NO floatarray[10] or floatarray[11], floatarray only goes from
	 * 0-9 ! So... if they don't exist, what memory did we just change? We must
	 * have overwritten some other variable's memory, or some internal state of
	 * the program. I hope it wasn't anything important!
	 *
	 * Hmm... I declared chararray right after the floatarray, I wonder if
	 * floatarray has now corrupted chararray...? */

	// print out the values of chararray
	for (i = 0; i < 10; i++ ) {
		printf("chararray[%d] = %c\n", i, chararray[i]);
	}

	/* Although this depends on the compiler, as of 2026, you're likely to see
	 * that the first two values of chararray have been corrupted by our array
	 * overflow! */

	return 0;

}

void print_ints(int *array, unsigned int num) {

	/* prints an array in comma-separated form */

	int i;

	printf("Printing %d ints starting from %p!\n", num, array);

	for (i = 0; i < num; i++) {

		printf("%d", array[i]);

		if (i + 1 < num) {

			printf(", ");

		} else {

			printf("\n");
		}

	}

}


