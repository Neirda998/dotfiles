#include <string.h>

#include "exec/exec_case.h"

#include "expand/expand.h"

#include "exec/exec_compound_list.h"

int exec_rule_case(struct rule_case_node *rule_case, struct env *env)
{
    rule_case->expression = expand_word(rule_case->expression, env);

    struct case_item_node *item = rule_case->case_clause->case_item;
    while (item)
    {
        // exec case_clause: iterating on each pattern from the clause.
        for (int i = 0; i < item->size ; ++i)
        {
            item->patterns[i] = expand_word(item->patterns[i], env);
            // exec case_item: matching case expression with item patterns.
            if (strcmp(rule_case->expression, item->patterns[i]) == 0)
                return exec_compound_list(item->statement, env);
        }
        item = item->next;
    }

    return 0;
}
