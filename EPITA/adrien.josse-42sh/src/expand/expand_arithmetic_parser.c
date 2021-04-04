#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expand/expand_arithmetic_lexer.h"
#include "expand/expand_arithmetic_parser.h"
#include "expand/expand_arithmetic_free.h"
#include "expand/expand_arithmetic_free_2.h"

#include "utils/memory.h"

static struct const_arithmetic *rule_const(struct a_lexer *a_lexer)
{
    struct const_arithmetic *rule = xcalloc(1, sizeof(*rule));
    struct a_token *token = a_peek(a_lexer, 1);

    if (token->type == U_OP)
    {
        while (token->type == U_OP)
        {
            rule->unaries = xrealloc(rule->unaries,
                (rule->unary_size + 1) * sizeof(enum arithmetic_u_op));
            rule->unary_size++;
            rule->unaries[rule->unary_size - 1] = token->u_op;
            a_token_free(a_pop(a_lexer, 1));
            token = a_peek(a_lexer, 1);
        }
    }
    if (token->type == L_PARENTHESIS)
    {
        a_token_free(a_pop(a_lexer, 1));
        rule->or = rule_or(a_lexer);
        if (!rule->or)
        {
            warnx("arithmetic error: missing expression");
            free(rule);
            return NULL;
        }
        token = a_peek(a_lexer, 0);
        if (token->type != R_PARENTHESIS)
        {
            warnx("arithmetic error: expected ')'");
            free_const(rule);
            return NULL;
        }
        a_token_free(a_pop(a_lexer, 0));
        return rule;
    }
    else if (token->type != NUMBER)
    {
        warnx("arithmetic error: expected value");
        free_const(rule);
        return NULL;
    }
    rule->num = strdup(token->value);
    a_token_free(a_pop(a_lexer, 0));
    return rule;
}

static struct pow_arithmetic *rule_pow(struct a_lexer *a_lexer)
{
    struct pow_arithmetic *rule = xcalloc(1, sizeof(struct pow_arithmetic));
    rule->consts = xcalloc(1, sizeof(struct const_arithmetic *));
    rule->size = 1;

    rule->consts[0] = rule_const(a_lexer);
    if (!rule->consts[0])
    {
        free(rule->consts);
        free(rule);
        return NULL;
    }

    struct a_token *token = a_peek(a_lexer, 0);
    while (token->type == B_OP && token->b_op == EXP)
    {
        a_token_free(a_pop(a_lexer, 0));
        rule->consts = xrealloc(rule->consts,
                    (1 + rule->size) * sizeof(struct const_arithmetic *));
        rule->size++;
        rule->consts[rule->size - 1] = rule_const(a_lexer);
        if (!rule->consts[rule->size - 1])
        {
            free_pow(rule);
            return NULL;
        }
        token = a_peek(a_lexer, 0);
    }
    return rule;
}

static struct times_arithmetic *rule_times(struct a_lexer *a_lexer)
{
    struct times_arithmetic *rule = xcalloc(1, sizeof(struct times_arithmetic));
    rule->pows = xcalloc(1, sizeof(struct pow_arithmetic *));
    rule->size = 1;

    rule->pows[0] = rule_pow(a_lexer);
    if (!rule->pows[0])
    {
        free_times(rule);
        return NULL;
    }

    struct a_token *token = a_peek(a_lexer, 0);
    while (token->type == B_OP &&
        (token->b_op == MULT || token->b_op == DIV))
    {
        enum arithmetic_b_op b_op = token->b_op;
        a_token_free(a_pop(a_lexer, 0));
        rule->pows = xrealloc(rule->pows,
                    (1 + rule->size) * sizeof(struct pow_arithmetic *));
        rule->size++;
        rule->pows[rule->size - 1] = rule_pow(a_lexer);
        if (!rule->pows[rule->size - 1])
        {
            free_times(rule);
            return NULL;
        }
        rule->pows[rule->size - 1]->op = b_op;
        token = a_peek(a_lexer, 0);
    }
    return rule;
}

static struct sum_arithmetic *rule_sum(struct a_lexer *a_lexer)
{
    struct sum_arithmetic *rule = xcalloc(1, sizeof(struct sum_arithmetic));
    rule->times = xcalloc(1, sizeof(struct times_arithmetic *));
    rule->size = 1;

    rule->times[0] = rule_times(a_lexer);
    if (!rule->times[0])
    {
        free_sum(rule);
        return NULL;
    }

    struct a_token *token = a_peek(a_lexer, 0);
    while (token->type == B_OP &&
        (token->b_op == PLUS || token->b_op == MINUS))
    {
        enum arithmetic_b_op b_op = token->b_op;
        a_token_free(a_pop(a_lexer, 0));
        rule->times = xrealloc(rule->times,
                    (1 + rule->size) * sizeof(struct times_arithmetic *));
        rule->size++;
        rule->times[rule->size - 1] = rule_times(a_lexer);
        if (!rule->times[rule->size - 1])
        {
            free_sum(rule);
            return NULL;
        }

        rule->times[rule->size - 1]->op = b_op;
        token = a_peek(a_lexer, 0);
    }
    return rule;
}

static struct bit_arithmetic *rule_bit(struct a_lexer *a_lexer)
{
    struct bit_arithmetic *rule = xcalloc(1, sizeof(struct bit_arithmetic));
    rule->sums = xcalloc(1, sizeof(struct sum_arithmetic *));
    rule->size = 1;

    rule->sums[0] = rule_sum(a_lexer);
    if (!rule->sums[0])
    {
        free_bit(rule);
        return NULL;
    }

    struct a_token *token = a_peek(a_lexer, 0);
    while (token->type == B_OP &&
        (token->b_op == BIT_AND || token->b_op == BIT_OR
        || token->b_op == BIT_XOR))
    {
        enum arithmetic_b_op op = token->b_op;
        a_token_free(a_pop(a_lexer, 0));
        rule->sums = xrealloc(rule->sums,
                    (1 + rule->size) * sizeof(struct sum_arithmetic *));
        rule->size++;
        rule->sums[rule->size - 1] = rule_sum(a_lexer);
        if (!rule->sums[rule->size - 1])
        {
            free_bit(rule);
            return NULL;
        }
        rule->sums[rule->size - 1]->op = op;
        token = a_peek(a_lexer, 0);
    }
    return rule;
}

static struct and_arithmetic *rule_and(struct a_lexer *a_lexer)
{
    struct and_arithmetic *rule = xcalloc(1, sizeof(struct and_arithmetic));
    rule->bits = xcalloc(1, sizeof(struct bit_arithmetic *));
    rule->size = 1;

    rule->bits[0] = rule_bit(a_lexer);
    if (!rule->bits[0])
    {
        free_and(rule);
        return NULL;
    }

    struct a_token *token = a_peek(a_lexer, 0);
    while (token->type == B_OP && token->b_op == LOG_AND)
    {
        a_token_free(a_pop(a_lexer, 0));
        rule->bits = xrealloc(rule->bits,
                    (1 + rule->size) * sizeof(struct bit_arithmetic *));
        rule->size++;
        rule->bits[rule->size - 1] = rule_bit(a_lexer);
        if (!rule->bits[rule->size - 1])
        {
            free_and(rule);
            return NULL;
        }
        token = a_peek(a_lexer, 0);
    }
    return rule;
}

struct or_arithmetic *rule_or(struct a_lexer *a_lexer)
{
    struct or_arithmetic *rule = xcalloc(1, sizeof(struct or_arithmetic));
    rule->ands = xcalloc(1, sizeof(struct and_arithmetic *));

    rule->ands[0] = rule_and(a_lexer);
    if (!rule->ands[0])
    {
        free_or(rule);
        return NULL;
    }
    rule->size = 1;

    struct a_token *token = a_peek(a_lexer, 0);
    while (token->type == B_OP && token->b_op == LOG_OR)
    {
        a_token_free(a_pop(a_lexer, 0));
        rule->ands = xrealloc(rule->ands,
                    (1 + rule->size) * sizeof(struct times_arithmetic *));
        rule->size++;
        rule->ands[rule->size - 1] = rule_and(a_lexer);
        if (!rule->ands[rule->size - 1])
        {
            free_or(rule);
            return NULL;
        }
        token = a_peek(a_lexer, 0);
    }
    return rule;
}

struct expr *parse_expression(struct a_lexer *a_lexer)
{
    struct expr *expr = xcalloc(1, sizeof(struct expr));

    expr->or = rule_or(a_lexer);
    if (!expr->or)
    {
        free(expr);
        return NULL;
    }

    a_token_free(a_pop(a_lexer, 0));

    struct a_token *token = a_peek(a_lexer, 0);
    if (token->type != END)
    {
        warnx("arithmetic error : unexpected token");
        free(expr->or);
        free(expr);
        return NULL;
    }
    a_token_free(a_pop(a_lexer, 0));

    return expr;
}
