#ifndef BOOP_H
#define BOOP_H

/* what is this ifndef, define, and endif stuff?
 *
 * It's not good to import function declarations more than once (because it
 * will appear to the compiler that you're defining multiple things with the
 * same names). 
 *
 * #ifndef BOOP_H means, "do the stuff between this line and #endif iff (if and
 * only if) BOOP_H is not defined." If we do it (because BOOP_H is not
 * defined), the very first thing we do is to #define BOOP_H! Why? So that if
 * something tries to #include this file again, we will skip all the
 * definitions -- in other words, to ensure that we only include this
 * information only once.
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
