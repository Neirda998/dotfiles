#include "exec/exec_if.h"

#include "exec/exec_compound_list.h"

int exec_else_clause(struct else_clause_node *else_clause, struct env *env)
{
    if (else_clause->condition)
    {
        if (exec_compound_list_break(else_clause->condition, env) == 0)
            return exec_compound_list_break(else_clause->body, env);
        if (else_clause->next)
            return exec_else_clause(else_clause->next, env);
        return 0;
    }
    else
        return exec_compound_list_break(else_clause->body, env);
}

int exec_rule_if(struct rule_if_node *rule_if, struct env *env)
{
    if (exec_compound_list_break(rule_if->condition, env) == 0)
        return exec_compound_list_break(rule_if->body, env);
    if (rule_if->else_clause)
        return exec_else_clause(rule_if->else_clause, env);
    return 0;
}
