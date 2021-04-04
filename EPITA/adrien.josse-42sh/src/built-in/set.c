#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "built-in/set.h"

#include "utils/memory.h"

int builtin_set(struct env *env)
{
    if (!env->argv[1])
    {
        warnx("set: too few arguments to set");
        return 2;
    }
    if (strcmp("-o", env->argv[1]) != 0 && strcmp("+o", env->argv[1]) != 0)
    {
        warnx("set: `%s` invalid argument", env->argv[1]);
        return 2;
    }
    if (!env->argv[2])
    {
        if (strcmp("-o", env->argv[1]) == 0)
            printf("noclobber\t%s\n",
            env->opts->is_noclobber == 1 ? "on" : "off");
        else
            printf("set noclobber\t%co\n",
            env->opts->is_noclobber == 1 ? '-' : '+');
        fflush(NULL);
    }
    else
        env->opts->is_noclobber = strcmp("+o", env->argv[1]) == 0 ? -1 : 1;
    return 0;
}
