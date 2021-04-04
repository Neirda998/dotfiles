#include <ctype.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "expand/variables.h"

#include "built-in/built_in.h"
#include "built-in/continue.h"

static int is_number(char *str)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

static int min(int a, int b)
{
    return a < b ? a : b;
}

int builtin_continue(struct env *env)
{
    if (get_argc(env->argv) > 2)
    {
        warnx("break: too many arguments");
        return 1;
    }
    char *num = env->argv[1];
    if (num && !is_number(num))
    {
        warnx("continue: %s: numeric argument required", num);
        return ((atoi(get_value(env, "?")) + 128) % 256);
    }

    int increase = num == NULL ? 1 : atoi(num);
    env->nb_continues += min(increase, env->loops_depth);

    return 0;
}
