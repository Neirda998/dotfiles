/**
** \file
** \brief interactive mode core features.
**
** Core file for the shell's interactive mode.
** This file contains a set of allocation functions that handle errors.
** It determines if the input stream is a terminal and,
** if it is the case, it sets up some of readline's global
** variables.
*/
#ifndef READLINE_H
# define READLINE_H

int caught; ///< global variable for signal handling.

/**
** Gets next line in stream.
** If the stream refers to a terminal, it uses readline; getline otherwise.
** Sets up readline's variables, especially the prompt.
** @param PS1 String of the default prompt for interactive mode.
** @param PS2 String of the continuation interactive prompt.
** @param is_open Interactive mode switch. If set to 0,
** the terminal is in interaction mode; if set to 0, the terminal
** is in continuation mode.
*/
char *get_next_line(const char *PS1, const char *PS2, int is_open);

/**
** Sets up signal handling for interactive mode.
*/
void setup_signal(void);

#endif /* ! READLINE_H */
