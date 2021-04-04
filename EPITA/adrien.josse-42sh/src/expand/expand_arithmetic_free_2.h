/**
** \file
** Header for expansion of arithmetic expression (free part, II).
*/

#ifndef EXPAND_ARITHMETIC_FREE_2_H
# define EXPAND_ARITHMETIC_FREE_2_H

#include "expand/expand_arithmetic_parser.h"

/**
** And rule de-allocation function.
** @param rule Rule to be freed.
*/
void free_and(struct and_arithmetic *rule);

/**
** Or rule de-allocation function.
** @param rule Rule to be freed.
*/
void free_or(struct or_arithmetic *rule);

#endif /* ! EXPAND_ARITHMETIC_FREE_2_H */
