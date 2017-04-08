# daVinci

<img src="https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.png" alt="screen shot of custom printf function">

## Description

This repo has our custom shell project, which attempts to replicate some of the
processes of the 'sh' shell or 'bash' shell.

### C language standard functions and system calls utilized

``access``, ``chdir``, ``close``, ``closedir``, ``execve``, ``exit``, ``fork``,
``free``, ``fstat``, ``getcwd``, ``getline``, ``kill``, ``lstat``, ``malloc``,
``open``, ``opendir``, ``perror``, ``read``, ``readdir``, ``signal``, ``stat``,
``strtok``, ``wait``, ``waitpid``, ``wait3``, ``wait4``, ``write``, ``_exit``

## Brief Synopsis

All files in this repository are designed to compile with GNU compiler
collection v. '``gcc 4.8.4``' in the linux environment from '``Ubuntu 14.04.5
LTS``'.  When compiled, the executable file replicates a 'shell' or command line
interpreter, which is a user interface used for access to an operating system's
services.  This shell has a set of custom built-in commands, and also integrates
with other commands located in the system's PATH.

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

* ``.r/header.h``: main header file that contains all necessary C standard
library headers, all our custom macro definitions, and all prototypes of all
functions in our custom shell application.
* ``./base_structs.h``: header file that contains all type definitions for all
structs.

### testing files
  * travis-ci
  * Makefile

## Authors

Bobby Yang - https://github.com/bobstermyang/  
David John Coleman II - http://www.davidjohncoleman.com/

## License

Public Domain, no copyright protection
