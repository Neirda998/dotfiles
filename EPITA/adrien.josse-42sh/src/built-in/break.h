/**
** \file
** Header for built-in break's function.
*/

#ifndef BREAK_H
# define BREAK_H

#include "input/env.h"

/**
** Built-in function `break`.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int builtin_break(struct env *env);

#endif /* ! BREAK_H */
