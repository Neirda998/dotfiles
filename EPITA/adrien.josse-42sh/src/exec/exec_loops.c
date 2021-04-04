#include <string.h>
#include <stdlib.h>

#include "exec/exec_loops.h"

#include "parser/loops.h"

#include "expand/expand.h"
#include "expand/variables.h"

#include "exec/exec_compound_list.h"

int exec_rule_while(struct rule_while_node *rule_while, struct env *env)
{
    int res = 0;
    env->loops_depth++;
    while (exec_compound_list_break(rule_while->condition, env) == 0)
    {
        if (env->nb_breaks > 0)
        {
            (env->nb_breaks)--;
            env->loops_depth--;
            return 0;
        }

        if (env->nb_continues > 0)
            (env->nb_continues)--;

        if (env->nb_continues)
        {
            env->loops_depth--;
            return 0;
        }

        res = exec_compound_list_break(rule_while->body->body, env);
    }
    if (env->nb_continues > 0)
        (env->nb_continues)--;

    env->loops_depth--;
    return res;
}

int exec_rule_until(struct rule_until_node *rule_until, struct env *env)
{
    int res = 0;
    env->loops_depth++;
    while (exec_compound_list_break(rule_until->condition, env) != 0)
    {
        if (env->nb_breaks > 0)
        {
            (env->nb_breaks)--;
            env->loops_depth--;
            return 0;
        }

        if (env->nb_continues > 0)
            (env->nb_continues)--;

        if (env->nb_continues)
        {
            env->loops_depth--;
            return 0;
        }

        res = exec_compound_list_break(rule_until->body->body, env);
    }
    if (env->nb_continues > 0)
        (env->nb_continues)--;

    env->loops_depth--;
    return res;
}

int exec_rule_for(struct rule_for_node *rule_for, struct env *env)
{
    rule_for->iterated = expand_words(rule_for->iterated,
                                      &rule_for->size, env);
    int res = 0;
    env->loops_depth++;
    for (int i = 0; i < rule_for->size; ++i)
    {
        set_value(env, strdup(rule_for->iterator),
                  strdup(rule_for->iterated[i]));
        if (env->nb_breaks > 0)
        {
            (env->nb_breaks)--;
            env->loops_depth--;
            return 0;
        }

        if (env->nb_continues > 0)
            (env->nb_continues)--;

        if (env->nb_continues)
        {
            env->loops_depth--;
            return 0;
        }

        res = exec_compound_list_break(rule_for->body->body, env);
    }

    if (env->nb_continues > 0)
        (env->nb_continues)--;

    env->loops_depth--;
    return res;
}
