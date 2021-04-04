#define _XOPEN_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <err.h>

#include "utils/memory.h"

#include "built-in/export.h"
#include "expand/expand.h"

static int is_end_of_name(char c)
{
    if (isblank(c))
        return -1;
    return c == '\n' || c == '\0' || c == '=';
}

static char *get_name(char *var)
{
    int idx = 0;
    while (!is_end_of_name(var[idx]))
        idx++;

    if (is_end_of_name(var[idx]) == -1)
        return NULL;

    return strndup(var, idx);
}

static int parse_opt(struct export_opt *opts, char *arg)
{
    for (int i = 1; arg[i]; ++i)
    {
        if (arg[i] == 'n')
            opts->is_n = 1;
        else if (arg[i] == 'p')
            opts->is_p = 1;
        else
            return 2;
    }
    return 0;
}

static void export_opt_print(void)
{
    extern char **environ;
    for (char **cur = environ; *cur; cur++)
        printf("declare -x %s\n", *cur);
}

int builtin_export(int argc, char **argv)
{
    struct export_opt *opts = xcalloc(1, sizeof(struct export_opt));
    int idx = 1;
    while (idx < argc)
    {
        int opt_ret;
        if (argv[idx][0] == '-')
            opt_ret = parse_opt(opts, argv[idx]);
        else
            break;

        if (opt_ret != 0)
        {
            warnx("export: invalid option");
            free(opts);
            return opt_ret;
        }
        idx++;
    }

    if (idx == argc)
    {
        export_opt_print();
        free(opts);
        return 0;
    }

    int ret = 0;
    for (; idx < argc; ++idx)
    {
        if (argv[idx][0] == '-')
        {
            warnx("export: unvalid argument");
            free(opts);
            ret = 2;
        }

        char *name = get_name(argv[idx]);
        if (!name)
        {
            warnx("export: unvalid argument");
            free(opts);
            ret = 2;
        }
        else
        {
            if (opts->is_n)
                unsetenv(name);
            else
            {
                char *value = strchr(argv[idx], '=');
                value = value ? strdup(value + 1) : NULL;
                setenv(name, value, 1);
                free(value);
            }
        }
        free(name);
    }

    free(opts);
    return ret;
}
