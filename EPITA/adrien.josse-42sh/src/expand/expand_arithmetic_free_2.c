#include <stdlib.h>

#include "expand/expand_arithmetic_free_2.h"

#include "expand/expand_arithmetic_free.h"
#include "expand/expand_arithmetic_parser.h"

void free_and(struct and_arithmetic *rule)
{
    if (rule)
    {
        for (int i = 0; i < rule->size; i++)
            free_bit(rule->bits[i]);
        free(rule->bits);
        free(rule);
    }
}

void free_or(struct or_arithmetic *rule)
{
    if (rule)
    {
        for (int i = 0; i < rule->size; i++)
            free_and(rule->ands[i]);
        free(rule->ands);
        free(rule);
    }
}
