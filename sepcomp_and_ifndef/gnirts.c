#include <stdio.h>
#include <stdlib.h> /* needed for malloc(), free() */
#include <string.h> /* needed for strncpy() */
#include "boop.h"   /* needed for boop() */ 

/* gnirts.c -- defines gnirts(), a string reversing function */

void gnirts(char *string) {

	boop(); // call the very important library function boop()

	int i; /* counter */
	unsigned int stringlen; /* length of input string to gnirts */
	stringlen = strnlen(string, 1048576);

	printf("length: %u\n", stringlen);

	/* make a temporary workspace on the heap */
	char *workspace = (char *)malloc(stringlen + 1);

	workspace[stringlen] = '\0'; /* make sure the null byte is there */

	/* reverse string into workspace */
	for (i = 0; i < stringlen; i++) {

		/* copy characters from the end of string into beginning of workspace */
		workspace[i] = string[(stringlen - 1) - i];

	}

	/* copy workspace back over string */
	strncpy(string, workspace, stringlen);

	/* free workspace */
	free(workspace);

	/* doesn't return a value, because it is a void function */

}
