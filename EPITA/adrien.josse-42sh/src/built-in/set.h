/**
** \file
** Header for built-in set's function.
*/

#ifndef SET_H
# define SET_H

#include "input/env.h"

/**
** Built-in function `set`.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int builtin_set(struct env *env);

#endif /* ! SET_H */
