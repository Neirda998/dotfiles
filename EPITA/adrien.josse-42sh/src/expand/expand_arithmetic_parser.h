/**
** \file
** Header for expansion of arithmetic expression (parser part).
*/

#ifndef EXPAND_ARITHMETIC_PARSER_H
# define EXPAND_ARITHMETIC_PARSER_H

#include "expand/expand_arithmetic_lexer.h"

/**
** Constant arithmetic rule structure.
** Contains:
** A pointer on an (hypothetic) or_rule.
** An array of (hypothetic) unary operators. (-, +, ~ or !)
** The size of unary operators array (0 if empty).
** The string that represents the value (number or variable_name)
*/
struct const_arithmetic
{
    struct or_arithmetic *or;
    enum arithmetic_u_op *unaries;
    int unary_size;
    char *num;
};

/**
** Power arithmetic rule structure.
** Contains:
** An array of constant rules.
** A binary operator used for times_rule exec. (* or /)
** The size of the constant rules array.
*/
struct pow_arithmetic
{
    struct const_arithmetic **consts;
    enum arithmetic_b_op op;
    int size;
};

/**
** Times arithmetic rule structure.
** Contains:
** An array of power rules.
** A binary operator used for sum_rule exec. (+ or -)
** The size of the power rules array.
*/
struct times_arithmetic
{
    struct pow_arithmetic **pows;
    enum arithmetic_b_op op;
    int size;
};

/**
** Sum arithmetic rule structure.
** Contains:
** An array of times rules.
** A binary operator used for bit_rule exec. (&, | or ^)
** The size of the times rules array.
*/
struct sum_arithmetic
{
    struct times_arithmetic **times;
    enum arithmetic_b_op op;
    int size;
};

/**
** Bitwise arithmetic rule structure.
** Contains:
** An array of sums rules.
** The size of the sums rules array.
*/
struct bit_arithmetic
{
    struct sum_arithmetic **sums;
    int size;
};

/**
** And arithmetic rule structure.
** Contains:
** An array of bits rules.
** The size of the bits rules array.
*/
struct and_arithmetic
{
    struct bit_arithmetic **bits;
    int size;
};

/**
** Or arithmetic rule structure.
** Contains:
** An array of and rules.
** The size of the sums rules array.
*/
struct or_arithmetic
{
    struct and_arithmetic **ands;
    int size;
};

/**
** Main structure of arithmetic expression.
** Contains:
** A rule or to exec.
*/
struct expr
{
    struct or_arithmetic *or;
};

/**
** Parsing function of arithmetic or_rule.
** @param a_lexer The arithmetic lexer to use.
** @return The struct of corresponding or rule.
*/
struct or_arithmetic *rule_or(struct a_lexer *a_lexer);

/**
** Function that parses the whole expression
** @param a_lexer The arithmetic lexer to use.
** @return The struct of corresponding expression.
*/
struct expr *parse_expression(struct a_lexer *a_lexer);

#endif /* ! EXPAND_ARITHMETIC_H */
