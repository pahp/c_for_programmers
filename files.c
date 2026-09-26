#include <stdio.h>		/* basic IO */
#include <stdlib.h>		/* standard library */
#include <fcntl.h>		/* file operations */
#include <unistd.h>		/* POSIX OS API (syscalls) */
#include <errno.h>		/* nice error handling */
#include <string.h>		/* string functions */

#define MAXMSG 256

/*******************************
 * FILE OPERATIONS IN C / UNIX *
 * ****************************/

/* This demonstration will show you some aspects for how to read and write
 * files in a UNIX environment using the C programming language.
 *
 * As an abstraction (i.e., regardless of how they are implemented), a file in
 * UNIX is a stream of bytes -- you can think of them as working like an array
 * that lives on disk, and -- since the data does is not normally available in
 * memory -- like an array for which you need to use read() and write() calls
 * (among others) to access. This is pretty similar to working with files in
 * almost every other programming language, primarily because those languages
 * borrowed the interface and API from UNIX.
 *
 * File operations also make system calls on your behalf! So, while the
 * functions you call are not, themselves, system calls, they make system calls
 * (or cause them to be made). Here are the actions this demo covers:
 */

void press_a_key(void) {
	/***********************************************
	 * get keyboard input and put it into a buffer *
	 ***********************************************/
	char line[MAXMSG];
	int i;
	printf("Press enter/return to continue or ^C to quit...\n");
	if (fgets(line, MAXMSG, stdin)) { // MAXMSG - 1; see man fgets
		/* we could do something with 'line' if we wanted to, but we 
		 * just want the program to pause here until the user hits enter.
		 */
	}
}

int main(int argc, char *argv[]) {
	
	/**************************
	 * file descriptors -- fd *
	 * ***********************/
   
	/* Classic C file descriptors (fd) are simply an integer which is an index
	 * into the array of open files in the process structure (process control
	 * block, or PCB) for the given process. (The kernel has an array of PCBs
	 * indexed by PID, and each PCB has an array of open files for the given
	 * process, indexed by fd.) 
	 *
	 * Recall that all processes start with three open
	 * files: 
	 * 	0 -- standard input
	 * 	1 -- standard output and 
	 * 	2 -- standard error. 
	 * 	Opening new files will create new file descriptors, usually in order.
	 */

	int ret; // place for return values (we will reuse this)
	int fd; // our file descriptor will go here
	char *filename; // first cli arg
	char *message;  // second cli arg

	if (argc >= 3) {
		// if there are enough params
		filename = argv[1]; /* filename to wite to */
		message = argv[2];  /* the thing to write into the file */

	} else {
		// they don't know how to use this program
		printf("Usage './files FILENAME \"DOUBLEQUOTED_STRING_OF_TEXT\"'\n");
		printf("To create / modify a file, please provide a filename.\n");
		printf("WARNING: This file will be truncated if it exists, so don't pick anything important!\n");
		return 1;

	}

	/*
	 * OPEN 
	 * ----
	 *
	 * To open a file, you provide a pathname, a mode for the file (e.g., read,
	 * write, read-write), and permissions bits for the file (how the
	 * permissions should be, e.g., if the file is being created). This
	 * provides a filehandle, which is a variable you can use to interact with
	 * the open file. In UNIX, calling an file-open function will return a
	 * filehandle to you (if it is successful).
	 *
	 * See 'man 2 open' for more information.
	 */

	/* open in write-only mode and truncate file if it exists */
	if ((fd = open(filename, O_WRONLY|O_TRUNC, S_IWUSR|S_IRUSR)) < 0) {
		printf("We had an error opening the file '%s' (error: %d)!\n", filename, errno); 

		/*
		 * PERROR 
		 * ------
		 *
		 * Many calls in UNIX will, if something goes wrong, return a negative
		 * number.  Sometimes the negative number indicates what went wrong.
		 * However, a common practice is to return -1 on any error, and set a
		 * value called 'errno' to a special value indicating the error. Then,
		 * you use a function, perror(STRING), which prints "STRING: " and then
		 * prints a human-readable explanation of the error in question (an
		 * interpretation of the value in errno).
		 */

		perror("Error opening the file"); // A wild perror appears!
										  
		return 1;

	} else {
		printf("We opened the file '%s' for WRITING. It is now file descriptor %d.\n", 
			   filename, fd);
		printf("The cursor position for fd %d is %ld.\n", fd, lseek(fd, 0, SEEK_CUR));
	}

	printf("We will now write the string \"%s\" into fd %d.\n", message, fd);

	/* WRITE
	 * -----
	 *
	 * Similarly, to write to a file, you provide the filehandle, a string or
	 * buffer to write from (a data source), and the number of bytes you want
	 * to write. The function will return the number of bytes it was actually
	 * able to write, which might be less than what you requested. To write to
	 * a file, the file must have been opened in a writable mode (write or
	 * read-write).
	 *
	 * See 'man 2 write' for more information.
	 */

	if ((ret = write(fd, message, strnlen(message, MAXMSG - 1))) < 0) {
		perror("write() returned an error");

		return 1;
	} 
	
	printf("The kernel wrote %d bytes on our behalf.\n", ret);

	/*************************
	 * stupid lseek() tricks *
	 * **********************/
	
	/* SEEK
	 * ----
	 *
	 * UNIX files have a "cursor", which is the point in the file that will
	 * be read or written by the next operation. When a file is first opened, the
	 * cursor is set at 0, which is the beginning of the file. Each subsequent
	 * operation will adjust the cursor accordingly. 
	 *
	 * Consider a file containing "ABCDEFG". When you open the file, the cursor
	 * will be set to 0 (i.e., pointing at the first character):
	 *
	 * 0123456
	 * ABCDEFG
	 * ^
	 *
	 * Reads and writes of N bytes will move the cursor forward N bytes.
	 *
	 * Sometimes, you need to change the cursor position, or learn what it is, and
	 * it would be silly to have to close and reopen the file to do that. So, the
	 * "seek" function can be used to reset or query the cursor position. To use
	 * seek, you call the function name with the filehandle, an signed integer
	 * offset, and a 'whence' argument ("whence" means "from where"). The seek
	 * function returns the new offset (which is often changed by the call).
	 *
	 * The three whence values are:
	 * - SEEK_SET -- relative to the beginning of the file
	 * - SEEK_CUR -- relative to the current cursor position
	 * - SEEK_END -- relative to the the end of the file
	 *
	 * You can see examples of this when you run the program and in the code,
	 * where it says lseek(fd, 0, SEEK_CUR), which returns the current position
	 * ("SEEK_CUR + 0"). If you wanted to know a different position relative to
	 * the cursor, you would change 0 to a different +/- integer.
	 */

	printf("After the write, the cursor position is %ld.\n", lseek(fd, 0, SEEK_CUR));
	press_a_key();
	 
	/*
	 * If you want to move it N bytes relative to the cursor, call lseek(fd, N,
	 * SEEK_CUR), where -N moves "back" and N moves forward.
	 */

	printf("Let's move the cursor backwards 1 position.\n");
	lseek(fd, -1, SEEK_CUR);
	printf("After the lseek(), the cursor position is %ld.\n", lseek(fd, 0, SEEK_CUR));
	press_a_key();

	/* If you want to reset the position to the beginning, you would call
	 * lseek(fd, 0, SEEK_SET), i.e., set the cursor to 0.
	 */

	printf("Let's reset the cursor to the beginning...\n");
	lseek(fd, 0, SEEK_SET);
	printf("Set cursor to the beginning; it is now: %ld.\n", lseek(fd, 0, SEEK_CUR));
	press_a_key();

	/*
	 * If you read() or write() bytes from/to the file, the cursor will be
	 * advanced by that many bytes:
	 */

	printf("If I write one char at cursor position 0, I'll overwrite the first character.\n");
	if ((ret = write(fd, "X", 1)) < 0) {
		perror("write() returned an error");
		return 1;
	} 
	printf("After the write, the cursor position is %ld.\n", lseek(fd, 0, SEEK_CUR));
	press_a_key();
	
	
	/* If you want to advance to the end, you would SEEK_END 0 (set it to the end value)
	 */

	printf("Seeking to the end of the file... ");
	lseek(fd, 0, SEEK_END);
	printf("it is now: %ld.\n", lseek(fd, 0, SEEK_CUR));
	press_a_key();
	
	/*
	 * See 'man 2 lseek' for more information.
	 */

	printf("Closing file %d...\n", fd);

	/* CLOSE
	 * -----
	 *
	 * To close a file, you just call the appropriate function with the
	 * filehandle as a parameter.
	 *
	 * READ: To read a file, you give the function a filehandle to read from, a
	 * buffer to read into, and a number of bytes to read (which should not be
	 * greater than the size of the buffer). The read call (whatever it is
	 * named) will put the data into the buffer, and it will return the number
	 * of bytes it was able to read (which might be less than you requested).
	 * To read a file, the filehandle must have be opened in a readable mode
	 * (read or read/write).
	 *
	 * See 'man 2 close' for more information.
	 */

	close(fd);
	printf("Closed.\n");

	press_a_key();

	printf("\n");

	/* now, let's re-open the file and read it */

	char readbuf[MAXMSG];
 
	if ((fd = open(filename, O_RDONLY, S_IWUSR|S_IRUSR)) < 0) { /* open in read-only mode */
		printf("We had an error opening the file '%s' (error: %d)!\n", filename, errno); 
		perror("Error opening the file");
		return 1;
	} else {
		printf("We opened the file '%s' for READING. It is now file descriptor %d.\n", filename, fd);
		printf("(same fd b/c its reused, not b/c the filename is the same)\n");
		printf("The cursor position for fd %d is %ld.\n", fd, lseek(fd, 0, SEEK_CUR));
	}

	printf("We will now read up to MAXMSG bytes from fd %d into readbuf.\n", fd);

	if ((ret = read(fd, readbuf, MAXMSG)) < 0) {
		perror("write() returned an error");
	} else {
		printf("The kernel read %d bytes into readbuf on our behalf.\n", ret);
		printf("After the read, the cursor position is %ld.\n", lseek(fd, 0, SEEK_CUR));
	}
	printf("The contents of readbuf are:\n%s\n", readbuf);
	
	close(fd);

	printf("I closed the file '%s'\n", filename);
	press_a_key();

	/* erase readbuf so that we can reuse it:
	 * the function memset(char *buf, char c, int nbytes) writes nbytes of char
	 * c into memory buffer buf. */
	printf("We will reuse readbuf later, so we'd better erase it!\n");
	printf("(read does not erase or clear readbuf in any way!)\n");
	memset(readbuf, '\0', MAXMSG);
	printf("After erasing, the contents of readbuf are:\n%s\n", readbuf);
	
	press_a_key();

	printf("\n");

	/* we can open a file in both read and write modes! */

	if ((fd = open(filename, O_RDWR, S_IWUSR|S_IRUSR)) < 0) { /* open in read-write mode */
		printf("We had an error opening the file '%s' (error: %d)!\n", filename, errno); 
		perror("Error opening the file");
		return 1;
	} else {
		printf("We opened the file '%s' READING/WRITING. It is now file descriptor %d.\n", filename, fd);
		printf("The cursor position for fd %d is %ld.\n", fd, lseek(fd, 0, SEEK_CUR));
	}

	printf("We will now read up to MAXMSG bytes from fd %d into readbuf.\n", fd);
	if ((ret = read(fd, readbuf, MAXMSG)) < 0) {
		perror("write() returned an error");
	} else {
		printf("The kernel read %d bytes into readbuf on our behalf.\n", ret);
		printf("After the read, the cursor position is %ld.\n", lseek(fd, 0, SEEK_CUR));
	}
	printf("The contents of readbuf are:\n%s\n", readbuf);
	memset(readbuf, '\0', MAXMSG); /* erase readbuf */
	press_a_key();

	/* now let's write to the file again */
	printf("We are going to write our message to fd %d again...\n", fd);
	printf("Since the cursor is at the end of the file, this will EXTEND the file.\n");
	
	press_a_key();
	
	if ((ret = write(fd, message, strnlen(message, MAXMSG))) < 0) {
		perror("write() returned an error");
	} else {
		printf("We wrote %d bytes to fd %d.\n", ret, fd);
		printf("After the write, the cursor position is %ld.\n", lseek(fd, 0, SEEK_CUR));
	}
	
	press_a_key();

	/* the file cursor now points to the end of the file. */
   
	printf("If we try reading the file here (at pos %ld), we won't get anything.\n",
		   lseek(fd, 0, SEEK_CUR));
	printf("We will now read up to MAXMSG bytes from fd %d into readbuf.\n", fd);

	press_a_key();
	
	if ((ret = read(fd, readbuf, MAXMSG)) < 0) {
		perror("write() returned an error");
	} else {
		printf("We read %d bytes from fd %d.\n", ret, fd);
		printf("After the read, the cursor position is %ld.\n", lseek(fd, 0, SEEK_CUR));
	}
	
	printf("The contents of readbuf are:\n%s\n", readbuf);

	if (ret == 0) {
		printf("Sure enough, there's nothing to show, because the cursor was already at the end of the file (byte %ld).\n", lseek(fd, 0, SEEK_CUR));
	} else {
		printf("This lonely message will never print.\n");
	}

	press_a_key();

	/* let's reset the cursor position to the beginning of the file and reread */
	printf("Resetting cursor to 0 and rereading...\n");
	lseek(fd, 0, SEEK_SET); /* set it to exactly zero */
	printf("Now the cursor for fd %d is %ld.\n", fd, lseek(fd, 0, SEEK_CUR));

	press_a_key();

	printf("We will now read up to MAXMSG bytes from fd %d into readbuf.\n", fd);
	if ((ret = read(fd, readbuf, MAXMSG)) < 0) {
		perror("write() returned an error");
	} else {
		printf("We read %d bytes from fd %d.\n", ret, fd);
		printf("After the read, the cursor position is %ld.\n", lseek(fd, 0, SEEK_CUR));
	}
	printf("The contents of readbuf are:\n%s\n", readbuf);
	memset(readbuf, '\0', MAXMSG);
	printf("Closing fd %d\n", fd);
	close(fd);

	press_a_key();

	printf("\n");

	/* FILE pointers */

	/* FILE pointers are a slightly more user-friendly and OS-friendly way to
	 * do file operations, although the do the same things in much the same
	 * way.
	 *
	 * The main difference, apart from the names, is that fread() and fwrite() buffer data rather than doing the write all at once. This means that a process can ask the kernel to write 1G in 1024 1M chunks, rather than making a write() system call with a 1G payload. This makes everyone happier.
	 *
	 * Overall, though, FILE pointer operations are very similar to the lower-level operations we just demoed.
	 */

	/* what are they? */

	printf("Demoing fancier file pointer file operations!\n");

	/* a FILE pointer is a pointer to a structure that contains some helpful
	 * metadata, etc. for this set of operations. The most important thing
	 * inside the FILE pointer is the file descriptor that references the open
	 * file.
	 *
	 * You pretty much never need to mess with the FILE pointer data -- just
	 * use the functions intended for users.
	 */

	/* declaring a FILE pointer */
	FILE *MYFILE; 

	/* opening a file */
	printf("Calling fopen() to open %s...\n", filename);
	MYFILE = fopen(filename, "r"); /* open file for reading */
	printf("Opened! See 'man fopen' for more information.\n");
	press_a_key();

	/* read from MYFILE */
	printf("Reading data from MYFILE...\n");
	printf("Use fread(data, chunksize, total, FILE) to read to a file!\n");
	printf("	data: pointer to data\n");
	printf("	chunksize: how much data to read at once\n");
	printf("	total: total amount to read\n");
	printf("	FILE: file that is open for writing\n");
	printf("fread() will perform multiple read() calls to complete this task.\n");
	printf("Buffering it like this is helpful for the OS and process.\n");
	ret = fread(readbuf, 1, MAXMSG - 1, MYFILE); /* reading in 1-byte chunks */
	printf("Read %d bytes from MYFILE (i.e., %s).\n", ret, filename);
	printf("The contents of readbuf are:\n%s\n", readbuf);
	memset(readbuf, '\0', MAXMSG);

	press_a_key();

	/* get current position of the cursor */
	printf("File pointers use ftell() to get the position.\n");
	ret = ftell(MYFILE);
	printf("The cursor in MYFILE is at position %d\n", ret);
	press_a_key();

	/* closing a file */
	printf("Use fclose() to close a file pointer.\n");
	fclose(MYFILE);
	printf("Closed. See 'man fclose' for more information.\n");
	press_a_key();

	/* opening for writing with truncation */
	printf("Open %s in write mode (w+), truncating it if it exists...\n", filename);
	MYFILE = fopen(filename, "w+");
	if (MYFILE == NULL) { /* something went wrong */

		perror("Couldn't open file: ");
		return 1;
	}
	printf("Opened the file!\n");
	press_a_key();
	
	 /* write message to MYFILE in one-byte chunks * length of the message */
	printf("Use fwrite(data, chunksize, total, FILE) to write to a file!\n");
	printf("	data: pointer to data\n");
	printf("	chunksize: how much data to write at once\n");
	printf("	total: total amount to write\n");
	printf("	FILE: file that is open for writing\n");
	printf("fwrite() will perform multiple write() calls to complete this task.\n");
	ret = fwrite(message, 1, strnlen(message, MAXMSG), MYFILE);
	printf("We wrote %d bytes to MYFILE.\n", ret);
	press_a_key();

	/* get current position of the cursor */
	printf("Let's find out where the cursor is, now.\n");
	ret = ftell(MYFILE);
	printf("The cursor in MYFILE is at position %d\n", ret);
	press_a_key();

	/* seek to start of MYFILE */
	printf("To change the position, use fseek(FILE, offset, whence), like lseek().\n");
	printf("Changing cursor to point to file start.\n");
	fseek(MYFILE, 0, SEEK_SET);
	ret = ftell(MYFILE);
	printf("The cursor in MYFILE is at position %d\n", ret);
	press_a_key();

	/* read from MYFILE */
	ret = fread(readbuf, 1, MAXMSG - 1, MYFILE);
	printf("Read %d bytes from MYFILE.\n", ret);
	printf("The contents of readbuf are:\n%s\n", readbuf);
	memset(readbuf, '\0', MAXMSG);
	press_a_key();

	/* get current position of the cursor */
	ret = ftell(MYFILE);
	printf("The cursor in MYFILE is at position %d\n", ret);
	press_a_key();

	printf("Closing MYFILE.\n");
	fclose(MYFILE);
	printf("Closed.\n");

	return 0;


}
