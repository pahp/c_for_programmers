#ifndef BOOP_H
#define BOOP_H

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

extern char boopstring[256]; /* a buffer for holding the string used by boop() */
/* we will use this in another file */

void boop(void); /* code in boop.c! */
/* boop() prints whatever boopstring is set to. It takes no parameters and returns nothing. 
 *
 * You can pretend that boop() is an important function that must be regularly
 * called. For this reason, this program imports boop.h in every file, and
 * calls boop() in every function.
 *
 * To support this, we made boop.h and boop.c.
 *
 * boop.h declares the things that boop.c will use / provide.
 * boop.c defines the variables and functions (it has the source). Programs can
 * include the code in boop.c by using #include "boop.h".
 *
 */

#endif
