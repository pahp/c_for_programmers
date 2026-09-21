#ifndef GNIRTS_H
#define GNIRTS_H

/* what is this ifndef, define, and endif stuff?
 *
 * It's not good to import function declarations more than once (because it
 * will appear to the compiler that you're defining multiple things with the
 * same names). 
 *
 * #ifndef GNIRTS_H means, "do the stuff between this line and #endif iff (if
 * and only if) GNIRTS_H is not defined." If we do it (because GNIRTS_H is not
 * defined), the very first thing we do is to #define GNIRTS_H! Why? So that if
 * something tries to #include this file again, we will skip all the
 * definitions -- in other words, to ensure that we only include this
 * information once.
 */

/* PRETEND THAT THIS IS A BIG LIBRARY OF STRING FUNCTIONS, EVEN THOUGH THERE'S
 * ONLY ONE STRING FUNCTION IN IT RIGHT NOW */

void gnirts(char *string); /* code in gnirts.c! */
/* gnirts() takes a pointer to a string and reverses the string in place. It
 * returns nothing. The string at the pointer address must not be longer than
 * one megabyte.*/

#endif
