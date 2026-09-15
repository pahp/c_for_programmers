	/****************
	 * strings in C *
	 * *************/

	/* 
	 * strings in C are simply character arrays (arrays of characters) that end
	 * with a special character, '\0', aka NULL, because it is the byte
	 * '00000000'. In other words, the string "foo" is an array holding the 
	 * characters 'f', 'o', 'o', '\0'. The NULL byte tells C's string handling
	 * code that it has reached the end of the string.
	 */

	char foo = "foo";
