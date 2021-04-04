#include <stdlib.h>

#include "free/if_free.h"

#include "free/compound_list_free.h"

void rule_if_node_free(struct rule_if_node *if_node)
{
    if (!if_node)
        return;
    else_clause_node_free(if_node->else_clause);
    compound_list_break_node_free(if_node->body);
    compound_list_break_node_free(if_node->condition);
    free(if_node);
}

void else_clause_node_free(struct else_clause_node *else_clause)
{
    if (!else_clause)
        return;
    else_clause_node_free(else_clause->next);
    compound_list_break_node_free(else_clause->body);
    compound_list_break_node_free(else_clause->condition);
    free(else_clause);
}
