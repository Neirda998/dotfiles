/**
** \file
** Header for built-in continue's function.
*/

#ifndef CONTINUE_H
# define CONTINUE_H

#include "input/env.h"

/**
** Built-in function `continue`.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int builtin_continue(struct env *env);

#endif /* ! CONTINUE_H */
