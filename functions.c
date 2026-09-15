#include <stdio.h>

/***********************
 * declaring functions *
 * ********************/

/* A function must be declared in a source file before it is used */

/* There are two ways this can work. 
 * First, the whole function can be declared and defined, like this:
 */

int add_one_to_x(int x) {

	/* this function takes in an integer, x, and returns the value of x + 1 */

	return x + 1;

}

/* The other way is to simply _declare_ the function... */

int sub_one_from_x(int x);

/* ... and then we can _define_ it elsewhere (see the bottom of this file for
 * the code for sub_one_from_x() */

/****************************************
 * function parameters and return types *
 * *************************************/

/* Functions can take multiple parameters, which are comma separated.  Every
 * parameter of a function needs a type, and, when called, the parameters must
 * be of the matching type.  
 *
 * The return type of a function is the type of result it produces.
 *
 * More complex types, like arrays or structures (described later) can be
 * passed to functions, but must be passed as a pointer (also described later).
 *
 * The following function, divide_float_by_int, takes in a float and an int,
 * and returns a float.*/

float divide_float_by_int(float number, int divisor) {

	return (number / divisor);

}

/* what does this function do? what does it return? */

char add_int_to_char(char a, int b) {

	return a + b;

}

/* main() takes in an int (the number of commandline parameters that have been
 * given), and an array of string pointers (each item in the array is a pointer
 * to a string component of the commandline input). The number of items in
 * *argv[] is the value of argc.
 *
 * main() returns an int, which is the return value of the program.
 */

int main(int argc, char *argv[]) {

	int value = 10;

	/* let's call some functions */

	printf("value + 1 is: %d\n", add_one_to_x(value));

	printf("value - 1 is: %d\n", sub_one_from_x(value));

	printf("pi / 2 is: %f\n", divide_float_by_int(3.14159265, 2));

	printf("%c + %d = %c\n", 'A', 13, add_int_to_char('A', 13));

	return 0;

}

int sub_one_from_x(int x) {

	/* this function takes in an integer, x, and returns x - 1 */

	return x - 1;

}


