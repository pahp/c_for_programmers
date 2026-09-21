#include <stdio.h>
#include "boop.h"

/* this file contains the code for average().
 *
 * If this were a real software project, perhaps this file would contain many
 * different types of mathematical functions. For this demo, though, it just
 * averages floats.
 */


float average(float *floats, unsigned int num) {

	boop(); // call the important library function boop()

	int i;
	float sum = 0;

	for (i = 0; i < num; i++) {

		/* add all the values in the array together */
		sum = sum + floats[i];

	}

	return sum / num; /* return the sum / number of elements */


}
