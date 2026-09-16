#include <stdio.h>
#include <stdlib.h>

/* this program will teach you about conditionals and loops in C 
 * I waited this far to get into these subjects so that we'd have some
 * interesting comparisions and loops to demonstrate. 
 */

int main(int argc, char *argv[]) {

	/********************************
	 * commandline argument strings *
	 * (i.e., program parameters)   *
	 * *****************************/

	/* recall that argc is the number of commandline arguments and
	 * *argv[] is an array of pointers to strings containing each command line
	 * argument.
	 */

	/* try running this program with different numbers of commandline
	 * arguments! You can run it without any arguments:
	 *
	 * ./strings_and_libraries
	 *
	 * ...or run it with several:
	 *
	 * ./strings_and_libraries foo bar baz
	 *
	 * NOTE: There's always at least 1 argument, which is the name of the
	 * command being executed.
	 */

	/***************************************************
	 * comparison operators and conditional statements *
	 * ************************************************/

	/* here is an if, else if, else statement to help us be grammatically
	 * correct */

	if (argc == 0) {

		printf("Impossible. But lets us demo if, else if, and else.\n");

	} else if (argc == 1 ) {

		printf("There is 1 command line argument.\n");

	} else {

		printf("There are %d command line arguments.\n", argc);

	}

	/* common numeric comparison operators in C:
	 * equality: ==
	 * inequality: !=
	 * less than: <
	 * less or equal: <=
	 * greater than: >
	 * greater or equal: >=
	 *
	 * Be careful not to use = instead of == -- it will happy do assignment!
	 *
	 * For comparing strings, you need to use functions like strncmp().
	 * If you try to compare two strings like this: (str1 == str2) it will
	 * compare their pointer values, which almost certainly is not what you
	 * want!
	 */


	/***********************
	 * the mighty for loop *
	 * ********************/

	printf("The commandline arguments are:\n");

	/* print out all the CLI arguments using a for loop
	 *
	 * Three things happen here:
	 * 1. i is set to 0 to start the loop
	 * 2. the loop will run WHILE i < 9
	 * 3. increment i (i++) each time
	 *
	 * (I could also have written i = i + 1 but i++ is a common shorthand.)
	 *
	 */

	int i;

	for (i = 0; i < argc; i++) { // initial, condition, increment

		/* print the index and the argument at argv[i] */
		printf("argv[%d] = \"%s\"\n", i, argv[i]);

		/* NOTE: to get printf to print " characters, I needed to escape them
		 * with a backslash (\). */

		/* Did you notice the %s substitution symbol? It's what you use to
		 * insert a string in a printf format string. */

	}


	/***************
	 * while loops *
	 * ************/
	 	 
	int x = 0;

	/* here is a 'while' loop in C */
	
	i = 0;

	while (i < 10) { // do this until i is not < 10

		i++;

	}

	printf("i = %d\n", i); // i should = 10
	
	
	
	/* a for loop with a conditional inside! */

	for (i = 0; i < 9; i++) {

		/* % (percent) in a math context is the modulo operator.
		 * i.e., 4 % 2 = 0, because 4 is divided evenly by 2.
		 */

		if (i % 2 == 0) { 
			printf("%d is even!\n", i);
		} else  {
			printf("%d is odd!\n", i);
		}
		
	}

				   
	/* ********************
	 * continue and break *
	 * *******************/

	/* loops in C can be manipulated using 'continue' and 'break'	
	 * 'continue' -- skip the rest of this loop, but keep looping 'break' --
	 * quit the loop altogether and keep executing
	 *
	 * Let's loop over the CLI arguments with some weird conditionals
	 */

	for (i = 0; i < argc; i++) {

		if (argv[i][0] == 'a') {
			/* The first character of the current argument is an 'a' */
			printf("Argument %d starts with 'a', and it's: \"%s\"\n", i, argv[i]);

		} else if (argv[i][1] == 'a') {
			/* Don't print an argument if the 2nd character is 'a'. */
			continue; // skip to the next loop iteration

		} else if (argv[i][0] == 'x') {
			/* Quit the loop if the first character of the current argument is
			 * an 'x' */
			printf("Argument %d starts with 'x' -- quitting...\n", i);
			break; // quit out of the loop
		} else {
			printf("Argument %d is: \"%s\"\n", i, argv[i]);
		}

	}
	printf("I'm done printing arguments now.\n");

	/* *************************************
	 * the 'switch' (i.e., case) statement *
	 * ************************************/

	/* A switch statement (called a 'case' statement in bash) is a special kind
	 * of conditional. You can write equivalent if/else statements, but switch
	 * statements can be more efficient and you might see one in the wild.
	 *
	 * A switch statement choose one of n paths based on the value of a
	 * variable. For our demo, we will convert the first proper argument from a
	 * string to a number, and switch based on the number.
	 *
	 /*  for more on switch/case statements: 
	  *  https://www.geeksforgeeks.org/c/c-switch-statement/
	  */

	long int arg1;
	if (argc > 1) { /* can only do this if there is a 1st arg */
		arg1 = strtol(argv[1], NULL, 10); /* see string tutorial */
	}

	switch (arg1) { /* we are going to switch based on value of arg1 */
		case 0: /* arg1 == 0 */
			printf("The first argument (%s) converted to 0.\n", argv[1]);
			break;
		case 13: /* arg1 == 13 */
			printf("The first argument (%s) converted to 13.\n", argv[1]);
			break;
		case 99: /* arg1 == 99 */
			printf("The first argument (%s) converted to 99.\n", argv[1]);
			break;
		default: /* else */
			printf("The argument (%s) didn't convert to 0, 13, or 99.\n", argv[1]);
			break;
	}

	return 0;

}
