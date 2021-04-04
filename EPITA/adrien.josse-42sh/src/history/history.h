/**
** \file
** Header for history functions.
*/

#ifndef HISTORY_H
# define HISTORY_H

/**
** Loads history function from 42sh_history file.
*/
void load_history(void);

/**
** Saves history function to 42sh_history file.
*/
void save_history(void);

/**
** Writes a new line in history of 42sh.
** @param str The new line to write in the history.
*/
void write_line_history(char *str);

/**
** Displays the history of 42sh.
*/
void display_history(void);

/**
** Built-in function `history`.
** @param ac The length of the vector av.
** @param av The vector of strings.
** @return Returns the error code of the execution.
*/
int builtin_history(int ac, char **av);

#endif /* ! HISTORY_H */
