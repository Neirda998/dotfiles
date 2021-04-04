/**
** \file
** Header for expansion of arithmetic expression (free part, I).
*/

#ifndef EXPAND_ARITHMETIC_FREE_H
# define EXPAND_ARITHMETIC_FREE_H

#include "expand/expand_arithmetic_parser.h"

/**
** Const rule de-allocation function.
** @param rule Rule to be freed.
*/
void free_const(struct const_arithmetic *rule);

/**
** Power rule de-allocation function.
** @param rule Rule to be freed.
*/
void free_pow(struct pow_arithmetic *rule);

/**
** Times rule de-allocation function.
** @param rule Rule to be freed.
*/
void free_times(struct times_arithmetic *rule);

/**
** Sum rule de-allocation function.
** @param rule Rule to be freed.
*/
void free_sum(struct sum_arithmetic *rule);

/**
** Bitwise rule de-allocation function.
** @param rule Rule to be freed.
*/
void free_bit(struct bit_arithmetic *rule);

#endif /* ! EXPAND_ARITHMETIC_FREE_H */
