#include <stdio.h> // this is how libraries are included

// this is a single-line comment

/* this is a 
   multi-line comment */


/* let's declare our 'main()' function. 
   The declaration of a function includes its return type, its name, and its
   arguments.

   "int main()" means that main() will return an integer (the return value of
   the program).

   main() has two arguments:

   	1) the first argument, 'argc' is an int (it's the number of parameters to main). 
	2) The second argument, 'char *argv[]' is a pointer to an array of character strings.
   We will explain that more later, but for now, you can think that argv[] is
   an array holding any command-line arguments that our program has.

*/

int main(int argc, char *argv[]) {

	// Let's print "Hello, World!" and start a new line.
	printf("Hello, World!\n");
	
	return 0; // return to the calling function without error (0)

}

// there is no calling function, so the program terminates!

/* TASK 1: Compile and execute the code!

   To compile the code, save your source code, and then run:

   gcc hello.c -o hello
   
   If you have errors, fix them and try again!
   
   When it compiles without errors, run the code by executing:
   
   ./hello
   
   If you forget the "-o hello" part, it will name the binary "a.out".
*/

/* TASK 2: Newline characters!

   The '\n' at the end of the printf input makes the terminal start a new
   line after the printf. This makes the command prompt start on a "new line."
      
   See what happens if you remove the '\n' from the string. You'll need to save
   your changes, recompile the code, and re-run it to see the change.
   
   What happens if you put two newlines at the end of the printf?
*/

