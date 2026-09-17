#include <stdio.h>

/**********
 * MACROS *
 * *******/

/* Macros are a way of assigning a piece of text to a NAME (the names don't
 * have to be capitalized, but they often are as an aid to readability). When
 * you compile your source, the C preprocessor will replace all the ocurrences
 * of NAME with the text data. Only then will it actually compile the code.
 * Since macros are not variables, they cannot be changed through assignment.
 *
 * Macros have a lot of really cool uses -- including many we won't be able to cover here.
 *
 * To define a macro, start a line with '#define', then the name (no spaces),
 * and then the text to use. 
 *
 * There's a lot to learn about macros, if you're interested:
 *
 * - https://www.tutorialspoint.com/cprogramming/c_macros.htm
 * - https://stackoverflow.com/questions/39821164/how-do-you-define-a-multiline-macro-in-c
 *
 * Anyway, we will use these macro values later in the program (they are
 * globally available because they aren't variables, they're text
 * substitutions).
 */

#define MAGIC_WORD "Elbereth" // https://nethackwiki.com/wiki/Elbereth
#define MAGIC_NUMBER 0xdeadbeef

/* notice that macros do NOT end in semicolons -- because they're not C! */


int main(int argc, char *argv[]) {

	/***********************
	 * common simple types *
	 * ********************/

	/* DECLARING VARIABLES
	 * C is a strongly-typed language, like Java. This means that variables of a certain
	 * type can only be used in ways that are appropriate for that type. It also means
	 * that the compiler knows what type they are, and will enforce these
	 * rules. Finally, for C it also means that variables are always of a
	 * certain size in bits. This restricts the maximum/minimum values of each
	 * type of variable.
	 */

	// You must declare variables before using them.
	
	/* TIP: all lines of actual C instructions (not counting lines starting with #
	 * or curly braces) must end with a semicolon. */

	int wholenum; // ints are integers -- whole numbers
	float realnum; // floats are floating-point real numbers
	char character; // chars are individual characters -- single bytes
	// we will talk about other types later!
	
	// assigning values is similar to other languages:
	
	int zero = 0; // you can also declare and define a var in one step
	wholenum=1; // whitespace is often optional, but it helps readability
	realnum =     3.141592653589; // wow, that's ugly, but legal
	
	/* characters are individual 8-bit bytes, and can be assigned as a number
	 * or as a single character offset with single quotes. E.g., */
	
	character = 'c'; // assigning the numeric value of character 'c'
	character = 57;  // assigning the number 57 (which fits into 8 bits)
	
	/* NOTE: Strings are arrays of characters that end with a special byte.
	 * We will discuss them later. */

	/* *****************************
	 * PRINTING OUTPUT WITH PRINTF *
	 ******************************/
	
	/*
	 * printf takes a variable number of parameters. 
	 * 1) first, it takes a 'format string' which is a string that MAY contain
	 *    special 'substitution symbols' where variables will be inserted.
	 * 2) it can take in any number of additional variables, one for each 
	 *    'substitution symbol'.
	 *
	 * Confused yet? Some examples will make it very clear.
	 */
	
	/* here's one that looks familiar... it is a format string, but it has no
	 * substitution symbols and so there's nothing but the format string. */

	printf("Hello, World!\n"); 

	// Now let's try substituting in some variable values:

	/* each variable type uses a different substitution symbol (also known as 
	 * "conversion specifiers")! 
	 * - use %d for an int
	 * - use %f for a real / float
	 * - use %c for a character (or %d for the numeric value of that char)
	 */
	printf("wholenum: %d, realnum: %f, character: %c\n", wholenum, realnum, character);

	// Note: the printf doesn't display all the digits in the float by default!

	/********************
	* FORMAT SPECIFIERS *
	********************/
	
	/* you can specify the amount of padding and the precision of types by changing
	 * the substitution symbols: */

	printf("wholenum: %03d, realnum: %03.4f\n", wholenum, realnum);

	/* I can tell it to print lots of digits from the float if I want */
	printf("realnum: %0.20f\n", realnum);

	// whoa, floats are weird, that is not the number I put into realnum!
	
	/* macros and printf */

	/* Remember our macros from before? We can print them, too. Remember that the NAME of the macro is replaced with the data / text part of the macro before the code is compiled.
	 */

	printf("The magic word is: %s\n", MAGIC_WORD); /* %s is for strings, more later! */
	printf("The magic number is: %08x\n", MAGIC_NUMBER); /* %08x is for hex */

	/* there are macros that are automatically available with some useful information... */

	printf("This printf is in %s at line %d.\n", __FILE__, __LINE__);
	
	/* printf can perform and display the results of calculations: */
	printf("%s:%d realnum - wholenum: %f\n", __FILE__, __LINE__, realnum - wholenum);
	printf("%s:%d wholenum - realnum: %f\n", __FILE__, __LINE__, wholenum - realnum);
	/* __FILE__ and __LINE__ can be really useful when "printf debugging" */

	/* note that the result type must match the printf! This won't work: */

	// printf("realnum - wholenum: %d\n", realnum - wholenum);

	/* try uncommenting it and seeing what happens... the issue is that it says
	 * the result is an int (%d) but the result is a float because one of the
	 * arguments is a float -- i.e., printf expects %f here, not %d. */

	/* integer division is what you'd expect -- as long as the result is a
	 * whole number */

	printf("6/3 is 2: %d\n", 6 / 3);

	/* A different case is integer division when the result is not a whole number!
	 * In that case, fractional part is thrown away, e.g.: */

	printf("2/3 is not 0: %d\n", 2 / 3);

	/* this happens because the arguments are both ints, so C assumes the result will
	 * also be an int. But the result (.667) is less than one, so the fractional part
	 * is discarded. Another way to think about it is that integer division is
	 * always rounded down. */

	/* if you want floating point numbers, it's easy -- just add a .0 to at
	 * least one of the arguments -- and change the substitution symbol! */

	printf("2/3 is not 0: %f\n", 2.0 / 3);


	/*********************************
	 * SIGNED and UNSIGNED variables *
	 ********************************/

	/* integers and chars can be SIGNED or UNSIGNED. Signed vars can be
	 * negative, while the minimum value for an unsigned variable is always 0.
	 *
	 * Previously we mentioned that variables have a specific size; for
	 * example, a char is always an 8-bit byte. There are only 256 possible
	 * 8-bit values (00000000 to 11111111). So, an unsigned char ranges from 0
	 * to 255, while a signed char ranges from -128 to 127. Integers are (as of
	 * this writing) commonly 32-bit values. That means that signed integers
	 * range from roughly -2.1 billion to 2.1 billion, while an unsigned
	 * integer ranges from 0 to ~4.3 billion.
	 *
	 * Values denoting sizes or absolute counts -- anything where it does not
	 * make sense to have a negative value -- (e.g., lengths, number of things,
	 * etc.) should always use unsigned variables, and sometimes the compiler
	 * will enforce this.
	 *
	 * The int type is guaranteed to be signed per the C standard. On systems
	 * using the gcc compiler, chars are signed by default.
	 */

 	char signedchar = 0; // assigning a char a numerical value
	unsigned char unsignedchar = 0; // this one is unsigned -- 0 or positive
	int signedint = 0; // can be negative, 0 or positive
	int unsignedint = 0; // can be 0 or positive

	/* now let's print the signed and unsigned variables */
	printf("unsignedchar = %u, signedchar = %d, signedint = %d, unsignedint = %u\n",
		   unsignedchar, signedchar, signedint, unsignedint); // should all be 0

	/* TWO THINGS TO NOTICE!
	 * 1) I broke this line of code across two lines of text for better readability!
	 * 2) Use the %u symbol for unsigned chars and ints. Use the %d symbol for
	 * signed chars (being used as 8-bit numbers) and ints.
	 */

	// now, let's do some math on these values!
	signedchar = signedchar - 1; // decrement
	unsignedchar--;  // also decrement (use ++ for increment)
	signedint = signedint - 1;
	unsignedint = unsignedint - 1;
	
	printf("unsignedchar = %u, signedchar = %d, signedint = %d, unsignedint = %u\n",
		   unsignedchar, signedchar, signedint, unsignedint);

	/**************************
	 * UNDERFLOW and OVERFLOW *
	 *************************/

	/* whoa, why are some values negative while others are positive?
	 *
	 * This happens because signed variables can "go negative" but unsigned
	 * variables can't.  And all variables will "wrap around" to the other end
	 * of their range if they are under- or overflowed. This is called "modulo
	 * arithmetic."
	 *
	 * In general, C programmers have to pay attention and make sure this
	 * doesn't happen when you don't want it to.
	 *
	 * Here are examples of chars under- and overflowing:
	 */

	unsignedchar = 255;
	signedchar = -128;

	printf("unsignedchar = %u, signedchar = %d\n", unsignedchar, signedchar);

	unsignedchar++; // this will cause unsignedchar to overflow and wrap!
	signedchar--;   // this will cause signedchar to underflow and wrap!

	printf("unsignedchar = %u, signedchar = %d\n", unsignedchar, signedchar);

	/*******************************
	 * VALUES LARGER THAN 32 BITS? *
	 ******************************/

	/*
	 * What if you need an int larger than 32-bits? In that case, you want 'long long'!
	 *
	 * You can always see how big a type is using the sizeof() function, which
	 * always returns the size of a type in bytes.
	 *
	 * Here are examples of both:
	 */

	long long int longlongint = 0;
	long long unsigned int longlongunsignedint = 0;

	printf("longlongint: %lld, longlongunsignedint: %llu\n", longlongint,
		   longlongunsignedint);

	/* note that I used the symbols "%lld" and "%llu" for long long int, and
	 * long long unsigned int. */

	printf("size of long long int: %lu, size of long long unsigned int: %lu\n", 
		   sizeof(long long int), sizeof(long long unsigned int));

	/* notice I used the symbol "%lu" for "long unsigned int" -- we have to use
	 * %lu because sizeof() returns a long unsigned int.
	 *
	 * Running the code, you'll see that both long long ints and long long
	 * unsigned ints are both 8 *bytes*, a.k.a. 64 bits.
	 *
	 * What happens when we subtract one from each?
	 *
	 * */

	longlongint--;
	longlongunsignedint--;

	printf("longlongint: %lld, longlongunsignedint: %llu\n", longlongint,
		   longlongunsignedint);

	return 0; // return to the calling function without error (0)

}
