/**
** \file
** Header for built-in export's function.
*/

#ifndef EXPORT_H
# define EXPORT_H

#include "input/env.h"

/*
** `export` options structure.
** Contains two boolean values.
*/
struct export_opt
{
    int is_n; ///< boolean value corresponding to the n option.
    int is_p; ///< boolean value corresponding to the p option.
};

/**
** Built-in function `export`.
** @param argc The length of the vector argv.
** @param argv The vector of strings.
** @return Returns the error code of the execution.
*/
int builtin_export(int argc, char **argv);

#endif /* ! EXPORT_H */
