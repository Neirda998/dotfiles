#include "exec/exec_compound_list.h"

#include "exec/exec_input.h"

int exec_compound_list(struct compound_list_node *cmp_lst, struct env *env)
{
    int ret = 0;
    for (struct and_or_node *cur = cmp_lst->and_or_nodes; cur; cur = cur->next)
        ret = exec_and_or(cur, env);
    return ret;
}

int exec_compound_list_break(struct compound_list_break_node *cmp_lst_brk,
                             struct env *env)
{
    int ret = 0;
    for (struct and_or_node *cur = cmp_lst_brk->and_or_nodes; cur;
        cur = cur->next)
    {
        if (!env->nb_breaks && !env->nb_continues)
            ret = exec_and_or(cur, env);
    }
    return ret;
}
