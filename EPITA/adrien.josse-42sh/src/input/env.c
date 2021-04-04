#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "utils/memory.h"

#include "exec/exec_funcdec.h"

#include "input/env.h"
#include "input/option.h"

#include "expand/expand.h"
#include "expand/variables.h"

static void vars_free(struct vars *vars)
{
    struct var *cur = vars->head;
    while (cur)
    {
        struct var *tmp = cur->next;
        free(cur->name);
        free(cur->value);
        free(cur);
        cur = tmp;
    }
    free(vars);
}

static struct env *set_special_vars(int argc, char **argv, struct env *env)
{
    char buffer[500];
    env = set_value(env, strdup("?"), strdup("0"));
    sprintf(buffer, "%d", getpid());
    env = set_value(env, strdup("$"), strdup(buffer));
    env = set_value(env, strdup("0"), strdup("42sh"));
    env->args = xcalloc(sizeof(char *), (env->args_size + 1));
    env->args[env->args_size] = strdup(argv[env->args_size]);
    env->args_size++;
    for (int i = 1; i < argc - env->opts->index + 1; i++)
    {
        env->args = xrealloc(env->args, sizeof(char *) * (env->args_size + 1));
        env->args[env->args_size] = strdup(argv[i - 1 + env->opts->index]);
        env->args_size++;
        //sprintf(buffer, "%d", i);
        //env = set_value(env, strdup(buffer),
        //                    strdup(argv[i - 1 + env->opts->index]));
    }
    sprintf(buffer, "%d", getuid());
    env = set_value(env, strdup("UID"), strdup(buffer));
    srand(time(NULL));
    return env;
}

struct env *init_env(int argc, char **argv)
{
    struct env *env = xcalloc(1, sizeof(struct env));

    env->opts = parse_options(argc, argv);
    env->vars = init_vars();
    env = set_special_vars(argc, argv, env);

    return env;
}

void env_free(struct env *env)
{
    for (int i = 0; i < env->env_vars_size; i++)
    {
        free(env->env_vars[i]);
    }
    free(env->env_vars);

    for (int i = 0; i < env->args_size; i++)
        free(env->args[i]);

    free(env->args);
    free_options(env->opts);
    vars_free(env->vars);
    clear_funclist(env->funcs);

    if (env->aliases)
    {
        for (int i = 0; i < env->aliases->size ; ++i)
        {
            free(env->aliases->data[i]->name);
            free(env->aliases->data[i]->substitution);
            free(env->aliases->data[i]);
        }
        free(env->aliases->data);
        free(env->aliases);
        env->aliases = NULL;
    }

    free(env);
}
