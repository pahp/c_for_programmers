#ifndef AVERAGE_H
#define AVERAGE_H

/* what is this ifndef, define, and endif stuff?
 *
 * It's not good to import function declarations more than once (because it
 * will appear to the compiler that you're defining multiple things with the
 * same names). 
 *
 * #ifndef AVERAGE_H means, "do the stuff between this line and #endif iff (if
 * and only if) AVERAGE_H is not defined." If we do it (because AVERAGE_H is
 * not defined), the very first thing we do is to #define AVERAGE_H! Why? So
 * that if something tries to #include this file again, we will skip all the
 * definitions -- in other words, to ensure that we only include this
 * information once.
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
