#ifndef GNIRTS_H
#define GNIRTS_H

/* what is this ifndef, define, and endif stuff?
 *
 * It's not good to import function declarations more than once (because it
 * will appear to the compiler that you're declaring multiple things with the
 * same names). 
 *
 * #ifndef FOO means, "if FOO is NOT DEFINED as a macro, do the stuff between
 * this line and the next #endif." 
 *
 * If FOO is not defined, that means this is the first time we have #included
 * it!  When we include it for the first time, the very first thing we do is to
 * #define FOO as a macro (it is defined but has no value)! Why? So that if
 * something tries to #include this file again, we will skip the code inside
 * the ifndef to ensure that we can't declare these things multiple times.
 */

/* PRETEND THAT THIS IS A BIG LIBRARY OF STRING FUNCTIONS, EVEN THOUGH THERE'S
 * ONLY ONE STRING FUNCTION IN IT RIGHT NOW */

void gnirts(char *string); /* code in gnirts.c! */
/* gnirts() takes a pointer to a string and reverses the string in place. It
 * returns nothing. The string at the pointer address must not be longer than
 * one megabyte.*/

#endif
