#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expand/expand_arithmetic_exec.h"

#include "utils/memory.h"
#include "utils/xstring.h"

#include "expand/expand_arithmetic_lexer.h"
#include "expand/expand_arithmetic_parser.h"
#include "expand/expand_arithmetic_free.h"
#include "expand/variables.h"

static long long expand_name(char *word, struct env *env)
{
    char *rep = get_value(env, word);
    long long num;
    if (is_number(rep))
        num = strtoll(rep, NULL, 10);
    else
        num = 0;
    return num;
}

static long long int unary_eval(long long int num, enum arithmetic_u_op op)
{
    if (op == U_PLUS)
        return num;
    else if (op == U_MINUS)
        return -num;
    else if (op == LOG_NOT)
        return !num;
    return ~num;
}

static long long int const_eval(struct const_arithmetic *rule, struct env *env)
{
    long long int num = 0;
    if (rule->or)
        num = or_eval(rule->or, env);
    else
    {
        if (is_number(rule->num))
            num = strtoll(rule->num, NULL, 10);
        else
            num = expand_name(rule->num, env);
    }
    for (int i = rule->unary_size - 1; i >= 0; i--)
        num = unary_eval(num, rule->unaries[i]);
    return num;
}

static long long int my_pow(int a, int b)
{
    if (b < 0)
        return 0;
    if (b == 0)
        return 1;
    int res = 1;
    for (int i = 0; i < b; i++)
        res *= a;
    return res;
}

static long long int pow_eval(struct pow_arithmetic *rule, struct env *env)
{
    int idx = rule->size - 1;
    long long res = const_eval(rule->consts[idx], env);
    idx--;
    while (idx >= 0)
    {
        if (res < 0)
        {
            warnx("exponent less than 0 error");
            res = 0;
        }
        else
            res = my_pow(const_eval(rule->consts[idx], env), res);
        idx--;
    }
    return res;
}

static long long int times_eval(struct times_arithmetic *rule, struct env *env)
{
    long long int res = pow_eval(rule->pows[0], env);
    for (int i = 1; i < rule->size; i++)
    {
        if (rule->pows[i]->op == MULT)
            res *= pow_eval(rule->pows[i], env);
        else
        {
            long long pow = pow_eval(rule->pows[i], env);
            if (pow == 0)
            {
                warnx("division by 0 error");
                res = 0;
            }
            else
                res /= pow;
        }
    }
    return res;
}

static long long int sum_eval(struct sum_arithmetic *rule, struct env *env)
{
    long long int res = times_eval(rule->times[0], env);
    for (int i = 1; i < rule->size; i++)
    {
        if (rule->times[i]->op == PLUS)
            res += times_eval(rule->times[i], env);
        else
            res -= times_eval(rule->times[i], env);
    }
    return res;
}

static long long int bit_eval(struct bit_arithmetic *rule, struct env *env)
{
    long long int res = sum_eval(rule->sums[0], env);
    for (int i = 1; i < rule->size; i++)
    {
        if (rule->sums[i]->op == BIT_AND)
            res = res & sum_eval(rule->sums[i], env);
        else if (rule->sums[i]->op == BIT_OR)
            res = res | sum_eval(rule->sums[i], env);
        else
            res = res ^ sum_eval(rule->sums[i], env);
    }
    return res;
}

static long long int and_eval(struct and_arithmetic *rule, struct env *env)
{
    long long int res = bit_eval(rule->bits[0], env);
    for (int i = 1; i < rule->size; i++)
        res = res && bit_eval(rule->bits[i], env);
    return res;
}

long long int or_eval(struct or_arithmetic *rule, struct env *env)
{
    long long int res = and_eval(rule->ands[0], env);
    for (int i = 1; i < rule->size; i++)
        res = res || and_eval(rule->ands[i], env);
    return res;
}

long long int expr_eval(struct expr *expr, struct env *env)
{
    if (!expr || !expr->or)
        return 0;
    return or_eval(expr->or, env);
}
