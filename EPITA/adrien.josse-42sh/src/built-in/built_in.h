/**
** \file
** Built-in functions.
*/

#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "input/env.h"

/**
** Get the number of strings in a vector of strings.
** @param argv A vector of strings.
** @return Returns the length of argv.
*/
int get_argc(char **argv);

/**
** The execution function of all the built-ins.
** @param env The execution environment
** @return Returns the error code of the execution.
*/
int exec_built_in(struct env *env);

#endif /* ! BUILT_IN_H */
