#include <stdlib.h>

#include "expand/expand_arithmetic_free.h"

#include "expand/expand_arithmetic_parser.h"
#include "expand/expand_arithmetic_free_2.h"

void free_const(struct const_arithmetic *rule)
{
    if (rule)
    {
        if (rule->num)
            free(rule->num);
        if (rule->or)
            free_or(rule->or);
        free(rule->unaries);
        free(rule);
    }
}

void free_pow(struct pow_arithmetic *rule)
{
    if (rule)
    {
        for (int i = 0; i < rule->size; i++)
            free_const(rule->consts[i]);
        free(rule->consts);
        free(rule);
    }
}

void free_times(struct times_arithmetic *rule)
{
    if (rule)
    {
        for (int i = 0; i < rule->size; i++)
            free_pow(rule->pows[i]);
        free(rule->pows);
        free(rule);
    }
}

void free_sum(struct sum_arithmetic *rule)
{
    if (rule)
    {
        for (int i = 0; i < rule->size; i++)
            free_times(rule->times[i]);
        free(rule->times);
        free(rule);
    }
}

void free_bit(struct bit_arithmetic *rule)
{
    if (rule)
    {
        for (int i = 0; i < rule->size; i++)
            free_sum(rule->sums[i]);
        free(rule->sums);
        free(rule);
    }
}
