/**
** \file
** Utils functions
*/

#ifndef UTILS_H
# define UTILS_H

#include "lexer/lexer.h"

/**
** Pop all the next NEW_LINE tokens.
** @param lexer The lexer structure.
*/
void skip_new_lines(struct lexer *lexer);

#endif /* ! UTILS_H */
