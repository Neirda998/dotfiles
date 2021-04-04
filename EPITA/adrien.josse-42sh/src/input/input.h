/**
** \file
** \brief manage input file stream - header.
**
** Opening and closing stream according to arguments.
** There are three differents cases:
** If the input is a string, it is opened with fmemopen
** and returned as a stream.
** If it is a file, it is opened with fopen and returned as a stream as well.
** The last case is when the input is from a terminal in interactive mode.
** In this case, no stream will be opened and input will be read from stdin.
*/
#ifndef INPUT_H
# define INPUT_H

#include <stdio.h>

/**
** Opens the fd corresponding to in_str.
** If flag_c is 1, then in_str is opened with fmemopen.
** If flag_c is 0, then in_str is the path of the file opened.
** @param flag_c Was the c flag given to 42sh.
** @param in_str String to be read or path of file to be read.
** @return Opened fd.
*/
FILE *open_input(int flag_c, char *in_str);

/**
** Closes input stream.
** @param input stream from which lines are read.
*/
void close_input(FILE *instream);

#endif /* ! INPUT_H */
