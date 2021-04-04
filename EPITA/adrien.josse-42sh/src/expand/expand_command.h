/**
** \file
** Header for expansion of commands functions.
*/

#ifndef EXPAND_COMMAND_H
#define EXPAND_COMMAND_H

#include "input/env.h"

/**
** Command expansion function.
** @param word The word where to perform the expansion.
** @param env The execution environment.
** @return Returns the expanded string.
*/
char *expand_commands(char *word, struct env *env);

#endif // ! EXPAND_COMMAND_H
