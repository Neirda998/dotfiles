/**
** \file
** Header for expansion of tildes functions.
*/

#ifndef EXPAND_TILDES_H
#define EXPAND_TILDES_H

#include "input/env.h"

/**
** The tilde expansion function.
** @param word The word where the tilde needs to be expanded.
** @param env The execution environment.
** @return Returns the resulted string after the tilde expansion.
*/
char *expand_tildes(char *word, struct env *env);

#endif // ! EXPAND_TILDES_H
