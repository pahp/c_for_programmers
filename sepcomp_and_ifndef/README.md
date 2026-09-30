# separate compilation and ifndefs

The files in this directory show you how to compile a binary based on multiple source files. It also shows you how to include one file in another.

To compile the program, run:

```
gcc prog.c average.c boop.c gnirts.c -o prog
```

This will produce the binary `prog`, which you can run using `./prog`.

Look at and read through all the files -- both the `.c` and the `.h` files.
