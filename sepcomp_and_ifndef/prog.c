#include <stdio.h>
#include "gnirts.h"  /* library to reverse a string */
#include "average.h" /* library to average floats */
#include "boop.h"    /* goes boop */

/************************************
 * SEPARATE COMPILATION AND IFNDEFS *
 * *********************************/

/* When programs get too big, or when the programmer wants to reuse code or
 * data -- especially across multiple programs -- it can be helpful to do
 * "separate compilation" -- have multiple files that we compile together into
 * one program.
 *
 * This demonstration will show you how to do that.
 *
 * This demo has one main program file and three "libraries". 
 * - prog.c -- this file -- the main program
 * - average.h/average.c -- a "math library" with a float averaging function
 * - gnirts.h/gnirts.c -- a "string library" with a func that reverses strings
 * - boop.h/boop.c -- a very important library called by all functions
 *
 * Notice that all the "libraries" have been included at the top of this file.
 * By convention, double quotes in an include indicate that the library is
 * local to the other source files, and not a system library, like stdio.h.
 *
 * To compile a program with multiple sources, you must name all the C files,
 * and one output file. The C files will be compiled and used to produce one
 * binary, e.g.:
 *
 * gcc prog.c average.c boop.c gnirts.c -o prog
 *
 * The above command will compile four c files and produce the binary 'prog'.
 *
 * Run 'prog' to see what it does, and then continue reading. 
 */

int main(int argc, char *argv[]) {

	float farray[] = {3.2434, 1.2343, 7.2342, 9.23423, 0.134586, 3.14};
	float faverage = average(farray, 6); // compute the average of these floats

	/* Did you notice what just happened? I called the function average(), but
	 * average is not a function defined in this file!
	 *
	 * It is declared in the header file average.h, and the code for it is in
	 * average.c. Through the magic of separate compilation, we can compile the
	 * source for that function and use it in our program.
	 *
	 * Average *itself* also includes boop.h/boop.c, which prints "BOOP!".
	 *
	 * Take a look at average.h and average.c for more information.
	 *
	 * In particular, check out how to use ifndef and define to make sure that
	 * the file is loaded in a way that will work.
	 */
	
	printf("The average of this array is: %f\n", average(farray, 6));

	char foo[] = "evian";

	/* Let's seen another example: */
	printf("The string %s ", foo);
	gnirts(foo);
	printf("... when written backwards is %s.\n", foo);

	/* gnirts.h/gnirts.c contains a function that reverses the string in a
	 * pointer "in place" (i.e., changes a string). It is also #included at the
	 * top of this file. Like average(), the function is declared in the header
	 * file but defined in the C file.
	 *
	 * gnirts() also imports and uses the boop() function.
	 *
	 * Take a look at gnirts.h and gnirts.c for more information.
	 */

	/* That's pretty much it! But you can use this to separate a large, complex
	 * project into multiple separate files / libraries, etc., and compile them
	 * together into one binary.
	 */


}
