/**
** \file
** Header for expansion of arithmetic expression (main part).
*/

#ifndef EXPAND_ARITHMETIC_H
#define EXPAND_ARITHMETIC_H

#include "input/env.h"

/**
** Main function of arithmetic expansion.
** @param word The string that represents the expression to expand.
** @param env The current environment structure.
** @return A string that represents the resulting number of expression.
*/
char *expand_arithmetics(char *word, struct env *env);

#endif // ! EXPAND_ARITHMETIC_H
