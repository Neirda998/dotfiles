#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "quote_len.h"

int begin_with(char *str, char *key)
{
    if (!str || !key)
        return 0;
    if (strncmp(str, key, strlen(key)) == 0)
        return 1;
    return 0;
}

enum quote_type is_quote(char *str)
{
    char *quotes[9] = {
        "\"", "\'", "`",
        "$((", "$(", "${",
        "))", ")", "}"
    };
    for (int i = 0; i < 9; i++)
    {
        if (begin_with(str, quotes[i]))
            return i + 1;
    }
    return NONE;
}

int quote_len(enum quote_type type)
{
    if (type == NONE)
        return 0;
    if (type == DOUBLE)
        return 1;
    if (type == SIMPLE)
        return 1;
    if (type == COMMAND)
        return 1;
    if (type == MATH_L)
        return 3;
    if (type == SUB_L)
        return 2;
    if (type == VAR_L)
        return 2;
    if (type == MATH_R)
        return 2;
    if (type == SUB_R)
        return 1;
    return 1;
}
