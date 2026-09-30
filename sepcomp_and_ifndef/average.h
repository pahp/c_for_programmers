#ifndef AVERAGE_H
#define AVERAGE_H

/* what is this ifndef, define, and endif stuff?
 *
 * It's not good to import function declarations more than once because the C
 * preprocessor will copy it multiple times which will result in you declaring
 * the same thing multiple times (which is a nono).
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

/* PRETEND THAT THIS IS A BIG LIBRARY OF MATH FUNCTIONS, EVEN THOUGH THERE'S
 * ONLY ONE MATH FUNCTION IN IT RIGHT NOW */

float average(float *floats, unsigned int num); /* code in average.c */
/* average() takes a pointer to an array of floats, and an unsigned integer
 * that determines the number of floats in the array. It sums all the floats,
 * and then divides the result by the number of floats. 
 *
 * It does not do anything to identify or stop overflow from happening.
 */

#endif
