#include <stdlib.h>

#include "free/case_free.h"

#include "free/compound_list_free.h"

void rule_case_node_free(struct rule_case_node *rule_case)
{
    if (!rule_case)
        return;

    case_clause_node_free(rule_case->case_clause);
    free(rule_case->expression);
    free(rule_case);
}

void case_clause_node_free(struct case_clause_node *case_clause)
{
    if (!case_clause)
        return;

    case_item_node_free(case_clause->case_item);
    free(case_clause);
}

void case_item_node_free(struct case_item_node *case_item)
{
    while (case_item)
    {
        struct case_item_node *tmp = case_item;
        case_item = case_item->next;

        compound_list_node_free(tmp->statement);
        for (int i = 0; i < tmp->size ; ++i)
            free(tmp->patterns[i]);
        free(tmp->patterns);
        free(tmp);
    }
}
