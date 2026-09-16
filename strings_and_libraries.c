#include <stdio.h>
#include <stdlib.h> /* new library: libc, the "standard C library" */
#include <string.h> /* new library: string manipulation functions! */

	/****************
	 * strings in C *
	 * *************/

	/* 
	 * strings in C are simply character arrays (arrays of characters) that end
	 * with a special character, '\0', aka NULL, because it is the byte
	 * '00000000'. 
	 *
	 * In other words, all C-strings are character arrays, but not all
	 * character arrays are C-strings (because not all character arrays end
	 * with '\0').
	 *
	 * Strings can be manually constructed using characters and array accesses,
	 * but the standard way is to enclose them in double quotes, e.g., "this is
	 * a string".
	 *
	 * For example, the string "foo" is an array holding the 
	 * characters 'f', 'o', 'o', '\0'. The NULL byte tells C's string handling
	 * code that it has reached the end of the string. Using double quotes
	 * always means that the null byte will be silently inserted at the end.
	 *
	 * Did you notice the weird thing about the space required to store a C-string?
	 * "foo" is a three-byte string, but it takes four bytes to store,
	 * because of the final (and invisible) '\0'! A C-string will *always*
	 * require one more byte at the end of the string to hold the '\0' that
	 * indicates the string's end.
	 *
	 * In this demonstration, we are going to mess around with C strings.
	 */
	
int main(int argc, char *argv[]) {


	/**********************************
	 * declaring and creating strings *
	 * *******************************/

	/* the easy way */
	char foo[] = "this is a string";
	/* this type of declaration automatically declares enough space in the
	 * foo[] array to hold the quoted string */
	printf("foo says: \"%s\"\n", foo); 
	/* %s is the substitution for a string. Notice that I had to escape the
	 * double-quote above in order to print it inside of a double-quoted string
	 * */


	/* the hard way */
	char bar[17]; /* declare a character array with 17 slots */

	/* fill bar one character at a time */
	bar[0] = 't';
	bar[1] = 'h';
	bar[2] = 'i';
	bar[3] = 's';
	bar[4] = ' ';
	bar[5] = 'i';
	bar[6] = 's';
	bar[7] = ' ';
	bar[8] = 'a';
	bar[9] = ' ';
	bar[10] = 's';
	bar[11] = 't';
	bar[12] = 'r';
	bar[13] = 'i';
	bar[14] = 'n';
	bar[15] = 'g';
	bar[16] = '\0'; /* the null byte! */
	/* this sring has NO empty space in it! */
	printf("bar says: \"%s\"\n", bar);

	/* you can change elements of a string as you might expect */

	char word[] = "flip";
	printf("%s\n", word);
	word[2] = 'o'; /* changing the third letter of baz */
	printf("%s\n", word);

	/* Here's a way to create READ-ONLY strings */
	char *baz = "this is a read-only string";
	printf("%s\n", baz);

	/* baz cannot be modified, because this type of declaration puts the text
	 * of baz not on the stack, but into the read-only portion of the binary
	 * (technically called the '.rodata' section, which can be thought of as
	 * the 'data' portion of the 'code' segment.  
	 *
	 * So, if you want to declare an array of length SIZE but you don't know
	 * what will be in it yet, use this method:
	 *
	 * char *string[SIZE];  // char array of exactly SIZE bytes
	 *
	 * If you know what you want its starting value and length to be, but you
	 * might want to change it, use this method:
	 *
	 * char string1[] = "your string"; // char array exactly fitting contents + '\0'
	 *
	 * If the strong won't be modified, you can use:
	 *
	 * char *string2 = "your string";
	 *
	 * For more on this weird issue, see: 
	 * https://stackoverflow.com/questions/164194/why-do-i-get-a-segmentation-fault-when-writing-to-a-char-s-initialized-with-a
	 */

	/****************************************
	 * What happens if the '\0' is missing? *
	 * *************************************/

	/* Recall that a C-string is a character array that ends with a '\0'. All C
	 * functions that operate on strings assume that the '\0' (the "null byte")
	 * is present. They typically iterate over the string in a loop until they
	 * reach the null byte. If the null byte is NOT present, then the string
	 * function will simply zoom off the end of the array and start iterating
	 * through increasing memory addresses until it either reaches a null byte
	 * ('\0') by happenstance, or until it reaches memory that it's not able to
	 * touch legally, like unallocated or kernel memory. When this happens, the
	 * process with "segfault," which is short for "Segmentation Fault." You'll
	 * (probably) learn about segments in your OS class.
	 *
	 * Let's see what happens when a string loses its '\0'!
	 */

	/* The string 'bar', above, has a '\0' in index 16. Let's remove it. */
	char one[] = "one";
	char two[] = "two";
	one[3] = '!'; // replace '\0' with a '!'
	
	/* now, let's print bar again... I wonder what will happen?! */
	printf("one without null byte: \"%s\"\n", one);

	/* While it's not guaranteed that this trick will work -- and because it is
	 * not guaranteed you should never do it -- you (in 2026) probably saw
	 * something longer than bar being printed, because the string in 'two'
	 * was read before reaching the null byte in the second string. (In other
	 * words, starting from 'one', there is one longer string with a '!' in the
	 * middle!)
	 *
	 * SO MANY BUGS HAPPEN BECAUSE NULL BYTES GET REMOVED!
	 * IT'S 10PM. DO YOU KNOW WHERE YOUR NULL BYTES ARE?
	 *
	 */


	/*********************
	 * string operations *
	 * ******************/

	/* There are many functions that operate on strings. These functions
	 * typically include 'str' in the functionname. Here are some of the most
	 * common:
	 *
	 * - strnlen(str, nbytes) -- get the length of the string up to nbytes
	 * - strncpy(dst, src, nbytes) -- copy src into dst up to nbytes
	 * - strncat(dst, src, nbytes) -- append src to dest up to nbytes
	 *    NOTE: strncat() assumes that buffer dst is big enough for dst + src + 1!
	 * - strncmp(s1, s2, nbytes) -- compares whether s1 and s2 are equal up to nbytes
	 * - strchr(str, c), strrchr(str, c) -- find first or last 'c' in str respectively
	 *    NOTE: does not have a byte limit -- dangerous!
	 * - strnstr(str, substr, nybtes) -- find 1st loc of substr in str up to nbytes
	 * - snprintf(dst, nbytes, FORMAT, ...) -- printf FORMAT and args (...) into dst 
	 *   but only print up to nbytes for safety
	 *
	 * NOTE: Functions (like strchr, strrchr, and strtok) do not have any
	 * limits -- they will go until they crash or find a null byte if the
	 * original null byte is missing. All of the other functions have older,
	 * insecure, "non-n" versions that you should avoid if possible.
	 * 
	 * The above list was partly drawn from: 
	 * https://www.geeksforgeeks.org/c/string-functions-in-c/
	 *
	 * To read the full instructions for these functions, including their
	 * required parameter types, search for 'funcname manpage' in your browser,
	 * or, on the termal, run 'man 3 funcname' (e.g., man 3 strnlen).
	 *
	 * Let's see some of these in action!
	 */

	/* length of string */
	printf("length of bar is %lu\n", strnlen(bar, 17));

	/* copy a string */
	char qux[34]; // new empty bigger buffer with 34 bytes of space
	strncpy(qux, bar, 17); // copy bar into qux (pronounced kwux)
	printf("qux now holds \"%s\"\n", qux);

	/* append one string to another */
	strncat(qux, bar, 17);
	printf("qux now holds \"%s\"\n", qux);

	/* test to see if two strings match */
	if (strncmp(foo, bar, 17) == 0) {
		printf("strncmp() says foo and bar match!\n");
	} else {
		printf("strncmp() says foo and bar DO NOT match!\n");
	}

	/* find the first occurrence of a character in a string --
	/* NOTE: strchr returns a pointer to the first occurrence of the character
	 */
	char *pos = strchr(foo, 's');
	long unsigned index = pos - foo; // the array index of the character 's'

	/* construct a string in a location up to nbytes long */
	snprintf(qux, 34, "The 1st 's' in foo is @ index %lu", index);

	/* let's print the string we just made */
	printf("qux is now: \"%s\"\n", qux);

	/************************************************
	 * converting strings to numbers and vice versa *
	 * *********************************************/

	/* CLI (command-line interface) parameters are strings, even if they are a
	 * string of a number, e.g., "123". If a program needs a numeric version of
	 * that string, you need to use a function to manually convert it to a
	 * number. (This happens automatically in many languages, like Python, but
	 * it is not automatic in C.
	 *
	 * The old-school way to do this conversion was a function called atoi()
	 * (ascii-to-integer). However, while you might still see it around, that
	 * function is not very secure, so it has been deprecated in favor of
	 * strtol() (string-to-long) and others.
	 */

	 /* Let's convert a CLI parameter to an integer. */

	long int number; // where we will put the integer
	
	/* converts argv[1] to a number and put it in 'number'.
	 * - NULL means we don't care about where the number ended in the string
	 * - 10 means the number is base 10 (the familiar number system)
	 */
	printf("\n");
	number = strtol(argv[1], NULL, 10);
	printf("Running strtol(\"%s\", NULL, 10) produced the number: %ld\n", argv[1], number);

	/* let's convert an integer to a string */

	char numberstring[256];
	snprintf(numberstring, 255, "%ld", number); /* prints number *into* numberstring */
	printf("I converted %ld back from a number to a string and got \"%s\"\n", number, numberstring);

	/* *********************************
	 * tip for managing string lengths *
	 * ********************************/

	 /* One way that I like to approach this is to declare a variable in my
	  * code like this:
	  */

	unsigned int slen = 64;

	/* ... and then use that to determine the size of every string buffer where
	 * I might modify the string: */

	char buf1[slen]; // a 64 byte array!
	/* ... */
	char bufn[slen]; // another 64 byte array!

	/* In this way, I know that all strings are 64 bytes long, so I always know
	 * a good number to use for 'nbytes' in string functions like the ones
	 * demonstrated above. If I need larger strings, I use a multiple of slen
	 * (or I just increase all strings to be the larger length. We have lots of
	 * memory now.
	 */

	/* That about covers it for strings... remember always make sure that
	 * buffers (arrays) have enough space for the characters, and that the end
	 * of the array always has a null byte! 
	 */
}
