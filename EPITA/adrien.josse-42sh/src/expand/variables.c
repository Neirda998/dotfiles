#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "expand/variables.h"

#include "utils/memory.h"
#include "utils/xstring.h"

#include "expand/expand.h"
#include "expand/expand_utils.h"

struct vars *init_vars(void)
{
    struct vars *vars = xcalloc(1, sizeof(struct vars));
    return vars;
}

static struct var *new_var(char *name, char *value)
{
    struct var *new = xcalloc(1, sizeof(struct var));
    new->name = name;
    new->value = value;
    return new;
}

struct env *set_value(struct env *env, char *name, char *value)
{
    env->vars->len++;
    struct var *cur = env->vars->head;
    if (!cur)
    {
        env->vars->head = new_var(name, value);
        return env;
    }

    while (cur->next)
    {
        if (strcmp(cur->name, name) == 0)
        {
            free(name);
            free(cur->value);
            cur->value = value;
            return env;
        }
        cur = cur->next;
    }

    if (strcmp(cur->name, name) == 0)
    {
        free(name);
        free(cur->value);
        cur->value = value;
        return env;
    }

    cur->next = new_var(name, value);
    return env;
}

static char *handle_special_values(struct env *env, const char *name)
{
    if (strcmp("RANDOM", name) == 0)
    {
        char buffer[500];
        sprintf(buffer, "%d", rand() % 32767);
        set_value(env, strdup("RANDOM"), strdup(buffer));
    }
    if (strcmp("SHELLOPTS", name) == 0)
    {
        if (env->opts->is_noclobber)
            return "noclobber";
        else
            return "";
    }
    if (strcmp("#", name) == 0)
    {
        char buffer[500];
        sprintf(buffer, "%d", env->args_size - 1);
        set_value(env, strdup("#"), strdup(buffer));
    }
    if (is_number(name) && strcmp("0", name) != 0)
    {
        int num;
        sscanf(name, "%d", &num);
        if (num >= env->args_size)
            return "";
        return env->args[num];
    }
    if (strcmp("@", name) == 0 || strcmp("*", name) == 0)
    {
        char *ifs = get_ifs(env);
        char *value = strdup("");
        for (int i = 1; i < env->args_size; i++)
        {
            value = xstrcat(value, strdup(env->args[i]));
            value = xstrcatchar(value, ifs[0]);
        }
        free(ifs);
        set_value(env, strdup("@"), strdup(value));
        set_value(env, strdup("*"), strdup(value));
        free(value);
    }
    return NULL;
}

char *get_value(struct env *env, const char *name)
{
    char *sp_val = handle_special_values(env, name);
    if (sp_val)
        return sp_val;
    struct var *cur = env->vars->head;
    while (cur)
    {
        if (strcmp(cur->name, name) == 0)
            return cur->value;
        cur = cur->next;
    }
    env->env_vars = xrealloc(env->env_vars, (env->env_vars_size + 1)
                             * sizeof(char *));
    char *tmp_val = getenv(name);
    if (!tmp_val)
        return "";
    env->env_vars[env->env_vars_size++] = strdup(tmp_val);
    return env->env_vars[env->env_vars_size - 1];
}

struct assignment *split_assign_word(char *assign_word, struct env *env)
{
    int idx = 0;
    while (assign_word[idx] && assign_word[idx] != '=')
        idx++;
    if (!assign_word[idx])
        errx(69, "There is an error in the parser.");
    struct assignment *assignment = xcalloc(1, sizeof(struct assignment));
    assignment->name = strndup(assign_word, idx);
    assignment->value = expand_word(strndup(assign_word + idx + 1,
                                            strlen(assign_word) - idx - 1),
                                    env);
    return assignment;
}
