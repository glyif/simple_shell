# MaryAnning shell

screen-shot
<img src="https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.png" alt="screen shot of custom printf function">

## Description

This repo has...

### C language standard functions and system calls utilized

``access``, ``chdir``, ``close``, ``closedir``, ``execve``, ``exit``, ``fork``,
``free``, ``fstat``, ``getcwd``, ``getline``, ``kill``, ``lstat``, ``malloc``,
``open``, ``opendir``, ``perror``, ``read``, ``readdir``, ``signal``, ``stat``,
``strtok``, ``wait``, ``waitpid``, ``wait3``, ``wait4``, ``write``, ``_exit``

## Brief Synopsis

This is a synopsis

## File List

* ``./example``: description

  #### functions contianed in this file:
  * ``example_func()``: description here

  #### files that contain modifier functions
  * ``./modifiers_example.c``: description

* ``./helper_funcs.c``: file that contains helper functions

  #### functions in helper file:
  * ``_putchar()``: function called ``_putchar()`` to write chars to standard
  output 1 at a time
  * ``_strlen``: custom function to find string length

### header files

* ``./holberton.h``: header file that contains all necessary included libraries
for all functions, the struct prototype and type definition for the struct,
and prototypes for all functions
* ``./man_simple_shell``: manual file

### main directory
  * this directory contains ``main()`` functions for testing custom .c files and
  testing the expected output of standard C version of ``printf()``
  * ``./dev/main/main.c``: tests expected output of standard ``printf()``
  function.  Can be compiled on its own - no need for other functions
  * ``./dev/main/custom_main.c``: tests actual output of custom ``_printf()``
  function
  * ``./dev/main/combo_main.c``: tests actual output of custom ``_printf()``
  function and expected output of ``printf()`` function together.  Most test
  cases are for standard functions.

## Authors

Bobby Yang - https://github.com/bobstermyang/
David John Coleman II - http://www.davidjohncoleman.com/

## License

Public Domain, no copyright protection
