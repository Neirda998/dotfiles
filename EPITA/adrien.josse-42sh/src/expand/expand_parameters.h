/**
** \file
** Header for expansion of parameters functions.
*/

#ifndef EXPAND_PARAMETERS_H
#define EXPAND_PARAMETERS_H

#include "input/env.h"

/**
** The parameters expansion function.
** @param word The word where to perform the expansion of parameters.
** @param env The execution environment.
** @return Returns the expanded string.
*/
char *expand_parameters(char *word, struct env *env);

#endif // ! EXPAND_PARAMETERS_H
