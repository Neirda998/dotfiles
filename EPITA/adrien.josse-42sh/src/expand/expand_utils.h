/**
** \file
** Header for utils expansion functions.
*/

#ifndef EXPAND_UTILS_H
#define EXPAND_UTILS_H

#include "input/env.h"

/**
** Replaces first occurence of replaced by replacement in str.
** @param str The string where to perform the replacement.
** @param replaced The string to replace.
** @param replacement The replacement of replaced.
** @return Returns
*/
char *expand_in_str(char *str, char *replaced, char *replacement);

/**
** Gets IFS string value.
** @param env The execution environment.
** @return Returns the string value of IFS.
*/
char *get_ifs(struct env *env);

#endif // ! EXPAND_UTILS_H
