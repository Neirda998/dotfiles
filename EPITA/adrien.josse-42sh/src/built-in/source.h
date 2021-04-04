/**
** \file
** Header for built-in source's function.
*/

#ifndef SOURCE_H
# define SOURCE_H

#include "input/env.h"

/**
** Built-in function `source`.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int builtin_source(struct env *env);

#endif /* ! SOURCE_H */
