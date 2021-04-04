#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "built-in/alias.h"

#include "utils/memory.h"

int alias_search(struct aliases *aliases, char *name)
{
    if (!aliases)
        return -1;
    for (int i = 0; i < aliases->size; i++)
    {
        if (strcmp(aliases->data[i]->name, name) == 0)
            return i;
    }
    return -1;
}

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

static struct alias *make_alias(char *arg)
{
    char *value = strchr(arg, '=');
    value = value ? strdup(value + 1) : NULL;
    char *name = get_name(arg);
    if (!name && value)
    {
        warnx("alias: '%s': invalid alias name", arg);
        free(value);
        return NULL;
    }
    struct alias *res = new_alias(name, value);
    free(name);
    free(value);
    return res;
}

static void print_alias(struct alias *alias)
{
    printf("%s='%s'\n", alias->name, alias->substitution);
    fflush(NULL);
}

int builtin_alias(struct env *env)
{
    char **argv = env->argv;

    if (!env->aliases)
        env->aliases = new_aliases();

    if (argv[1] == NULL)
    {
        for (int i = 0; i < env->aliases->size; i++)
            print_alias(env->aliases->data[i]);
        return 0;
    }
    int ret = 0;
    for (int i = 1; argv[i]; i++)
    {
        struct alias *alias = make_alias(argv[i]);
        int search = alias_search(env->aliases, alias->name);
        if (!alias)
            ret = 1;
        else if (!alias->substitution)
        {
            if (search == -1)
            {
                warnx("alias: %s: not found", alias->name);
                free(alias);
                ret = 1;
            }
            else
            {
                print_alias(alias);
                free(alias);
            }
        }
        else
        {
            if (search == -1)
                aliases_insert(env->aliases, alias);
            else
            {
                free(env->aliases->data[search]->substitution);
                env->aliases->data[search]->substitution = alias->substitution;
                free(alias->name);
                free(alias);
            }
        }
    }
    return ret;
}

void delete_aliases(struct env *env)
{
    if (!env->aliases)
        return;
    while (env->aliases->size)
        aliases_delete(env->aliases, 0);
    free(env->aliases->data);
    free(env->aliases);
    env->aliases = NULL;
}

char *alias_expand(char *str, char *prev, char *next, int idx)
{
    int p_len = strlen(prev);
    int n_len = strlen(next);
    int s_len = strlen(str);
    char *res = xcalloc(s_len - p_len + n_len + 1, sizeof(char));

    for (int i = 0; i < idx; i++)
        res[i] = str[i];
    int i = idx;
    while (i - idx < n_len)
    {
        res[i] = next[i - idx];
        i++;
    }
    int j = idx + p_len;
    while (j < s_len)
    {
        res[i] = str[j];
        i++;
        j++;
    }
    free(str);
    return res;
}

int builtin_unalias(struct env *env)
{
    char **argv = env->argv;
    int is_a = 0;

    if (!argv[1])
    {
        warnx("unalias: usage: unalias [-a] name [name ...]");
        return 2;
    }
    int idx = 1;
    while (argv[idx] != NULL && *argv[idx] == '-')
    {
        int j = 1;
        while (argv[idx][j])
        {
            if (argv[idx][j] != 'a')
            {
                warnx("unalias: -%c: invalid option", argv[idx][j]);
                return 1;
            }
            is_a = 1;
            j++;
        }
        idx++;
    }
    int ret = 0;
    if (is_a)
    {
        delete_aliases(env);
        return 0;
    }
    for (int i = idx; argv[i] != NULL; i++)
    {
        int search = alias_search(env->aliases, argv[i]);
        if (search == -1)
        {
            warnx("unalias: %s: not found", argv[i]);
            ret = 1;
        }
        else
            aliases_delete(env->aliases, search);
    }
    return ret;
}
