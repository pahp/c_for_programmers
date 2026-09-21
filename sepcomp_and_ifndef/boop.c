#include <stdio.h>
#include <string.h>
#include "boop.h"

/* this file obeys the UNIX philosophy -- 
 * it  does one thing and does it well */


void boop(void) {

	char boopstring[256]; /* we must re-declare boopstring from boop.h here */

	strncpy(boopstring, "BOOP!", 255); /* setting the boopstring here */

	printf("%s\n", boopstring); 

}
