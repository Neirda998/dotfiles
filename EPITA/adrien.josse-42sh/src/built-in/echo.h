/**
** \file
** Header for built-in echo's function.
*/

#ifndef ECHO_H
# define ECHO_H

/*
** `echo` options structure.
** Contains an index and two boolean values.
*/
struct echo_options
{
    int e;     ///< boolean value corresponding to the e option.
    int n;     ///< boolean value corresponding to the n option.
    int index; ///< the index in the argv environment variable after options.
};

/**
** Built-in function `echo`.
** @param ac The length of the vector av.
** @param av The vector of strings.
** @return Returns the error code of the execution.
*/
int builtin_echo(int ac, char **av);

#endif /* ! ECHO_H */
