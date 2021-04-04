/**
** \file
** Header for built-in exit's function.
*/

#ifndef EXIT_H
# define EXIT_H

/**
** Built-in function `exit`.
** @param ac The length of the vector av.
** @param av The vector of strings.
** @return Returns the error code of the execution.
*/
int builtin_exit(int ac, char **av);

#endif /* ! EXIT_H */
