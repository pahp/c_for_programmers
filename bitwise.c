#include <stdio.h>

/**********************
 * BITWISE OPERATIONS *
 * *******************/

/* While people argue about whether C is a "low-level" language or not (where
 * "low-level" is meant in the engineering sense of "detail oriented" or "low
 * abstraction"), it is the case that C is often used when people need almost
 * direct access to hardware, but where coding in machine language would be
 * both tedious and non-portable. 
 *
 * Because of these low-level needs, C includes the ability to perform certain
 * operations on the underlying bits of a variable or a memory location. These
 * operations are called "bitwise operations" because they manipulate the bits
 * of the underlying data.
 *
 * There are basically two types of bitwise operators. 
 *
 * One type of operator takes in one memory location and outputs a modified
 * version of that input.  An example of this type are the "bitshift"
 * operations x<<y and x>>y, which shift the bits of x to the left or right by
 * y bits.
 *
 * The other type of operator takes in two inputs and performs an operation
 * over corresponding bits of the input. Examples of these operations are
 * binary AND (&), OR (|), and XOR (^).
 *
 * This demo will cover some of the more common operators of these types.
 */


int main(int argc, char *argv[]) {

	/****************
	 * bit shifting *
	 * *************/

	/* You can shift the bits of a variable left or right by n
	 * positions using the << and >> operators, respectively.
	 *
	 * Use x << y to shift x to the left by y bits.
	 * Use x >> y to shift x to the right by y bits.
	 *
	 * Both << and >> "shift in" zeros as they shift bits out. In other words,
	 * << and >> are not binary *rotate*. For example, shifting 10000001 one
	 * position to the left would return 00000010, *not* 00000011.
	 *
	 * We'll take in two characters from the commandline and do some binary
	 * operations on them.
	 */

	if (argc < 2) {

		printf("bitwise -- a demonstration of bitwise operators\n");
		printf("Usage: bitwise CHARACTER1 CHARACTER1\n\n");
		printf("CHARACTERn is one ASCII character.\n");
		printf("(Strings can be provided, but only the first character will be used.)\n");
		printf("\n");

		return 1;
	}

	unsigned char x = (unsigned char)argv[1][0]; // the first char of the 1st argument
	unsigned char y = (unsigned char)argv[2][0]; // the first char of the 2nd argument

	/****************
	 * bit shifting *
	 * *************/

	unsigned int num = 0x80000001;
	int i = 0;

	printf("%s:%d - Let's shift some bits!\n", __FILE__, __LINE__);

	printf("num is 0x%08x\n", num);

	for (i = 0; i < 16; i++) {
		printf("num left-shifted %d bits is hex 0x%08x or decimal %d\n", 
			   i, num<<i, num<<i);
	}

	for (i = 0; i < 16; i++) {
		printf("num right-shifted %d bits is hex 0x%08x or decimal %d\n", 
			   i, num>>i, num>>i);
	}

	/*****************************
	 * bitwise binary operations *
	 ****************************/

	/* There are sometimes cases, particularly in low level code, where you
	 * find yourself wanting to do bitwise binary operations, i.e., bitwise
	 * and, or, or xor. Consider two 8-bit values, A and B. Bitwise "and" of A
	 * and B (written A & B) will produce a new value with ones only in the bit
	 * positions where A and B both had ones.
	 */

	printf("\n");
	printf("%s:%d - Let's do some bitwise logic operations!\n", __FILE__, __LINE__);
	printf("Change the 1st and 2nd arguments of the program to change the chars!\n");
	printf("char x = '%c' is hex 0x%02x or decimal %d\n", x, x, x);
	printf("char y = '%c' is hex 0x%02x or decimal %d\n", y, y, y);

	printf("0x%02x & 0x%02x == 0x%02x\n", x, y, x & y);
	printf("0x%02x | 0x%02x == 0x%02x\n", x, y, x | y); // useful for setting bits
	printf("0x%02x ^ 0x%02x == 0x%02x\n", x, y, x ^ y);

	/*******************************************
	 * testing whether a particular bit is set *
	 * ****************************************/

	/* sometimes it is important to know if a particular bit in a value is set.
	 * We can use combinations of bitwise and other operations to test values.
	 */

	printf("\n%s:%d - Does the char x have the 1 (rightmost) bit set?\n", 
		   __FILE__, __LINE__);

	if ((x & 0x01) == 0x01) {

		printf("Yes, the 1 bit of x (0x%02x) is set.\n", x);

	} else {
		
		printf("No, the 1 bit of x (0x%02x) is NOT set.\n", x);

	}

	return 0;

}
