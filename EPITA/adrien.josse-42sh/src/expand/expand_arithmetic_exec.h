/**
** \file
** Header for expansion of arithmetic expression (execution part).
*/

#ifndef EXPAND_ARITHMETIC_EXEC_H
# define EXPAND_ARITHMETIC_EXEC_H

#include "input/env.h"

# include "expand/expand_arithmetic_parser.h"

/**
** Arithmetic or rule evaluation.
** @param rule Or rule to be evaluated.
** @param env Current environment structure (for variable expanding)
** @return The integer result of evaluation.
*/
long long int or_eval(struct or_arithmetic *rule, struct env *env);

/**
** Arithmetic expression evaluation.
** @param expr Expression to be evaluated.
** @param env Current environment structure (for variable expanding)
** @return The integer result of expression evaluation.
*/
long long int expr_eval(struct expr *expr, struct env *env);

#endif /* EXPAND_ARITHMETIC_EXEC_H */
