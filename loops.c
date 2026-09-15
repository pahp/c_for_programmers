#include <stdio.h>

int main(int argc, char *argv[]) {

	/*********
	 * loops *
	 * ******/
	 	 
	int x = 0;
	int i;

	/* here is a 'while' loop in C */
	
	i = 0;

	while (i < 10) { // do this until i is not < 10

		i++;

	}

	printf("i = %d\n", i); // i should = 10
	
	
	/* We can also do 'for' loops:
	 *
	 * Three things happen here:
	 * 1. i is set to 0 to start the loop
	 * 2. the loop will run WHILE i < 9
	 * 3. increment i (i++) each time
	 *
	 * (I could also have written i = i + 1 but i++ is a common shorthand.)
	 *
	 */
	
	for (i = 0; i < 9; i++) {

		
		/*****************
		 * Conditionals! *
		 ****************/
		
		/* C, of course, has if, then and else if statements.
		 * They work pretty much the way you'd expect. */
		
		/* % (percent) in a math context is the modulo operator.
		 * i.e., 4 % 2 = 0, because 4 is divided evenly by 2.
		 */

		if (i % 2 == 0) { 
			printf("%d is even!\n", i);
		} else  {
			printf("%d is odd!\n", i);
		}
		
	}

				   
       /* continue and break
	* loops in C can be manipulated using 'continue' and 'break'	
	* 'continue' -- skip the rest of this loop, but keep looping
	* 'break' -- quit the loop altogether and keep executing
	*
	* here's an example!
	*/

	for (i = 0; i < 9; i++) {

		/*********************
		 * this is terrible peter, fix it!
		 *************************/

		if (i == 9) {

			// the for loop says we'll go until 10, but let's quit when we get to 9
			printf("i == %d, let's quit the for loop!\n", i);
			break; // quit the for loop (this is weird code, but it's just an example)

		} else if (i % 2 != 0) {
			/* note I tested if i % 2 is NOT equal to 0!
			 * you can use all the normal comparators, like:
			 * <, >, <=, >=, ==, and !=
			 * These operators do NOT work for strings... we'll discuss that later!
			 */
			continue; // if the number is odd, skip this loop
		}

		printf("The number %d must be even, because we skipped all odd loops!\n", i);
	
	}

	return 0;

}
