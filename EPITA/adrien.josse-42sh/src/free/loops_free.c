#include <stdlib.h>

#include "free/loops_free.h"

#include "free/compound_list_free.h"

void do_group_node_free(struct do_group_node *do_group)
{
    if (!do_group)
        return;

    compound_list_break_node_free(do_group->body);
    free(do_group);
}

void rule_while_node_free(struct rule_while_node *rule_while)
{
    if (!rule_while)
        return;

    compound_list_break_node_free(rule_while->condition);
    do_group_node_free(rule_while->body);
    free(rule_while);
}

void rule_until_node_free(struct rule_until_node *rule_until)
{
    if (!rule_until)
        return;

    compound_list_break_node_free(rule_until->condition);
    do_group_node_free(rule_until->body);
    free(rule_until);
}

void rule_for_node_free(struct rule_for_node *rule_for)
{
    if (!rule_for)
        return;

    free(rule_for->iterator);
    for (int i = 0; i < rule_for->size ; ++i)
        free(rule_for->iterated[i]);
    free(rule_for->iterated);
    do_group_node_free(rule_for->body);
    free(rule_for);
}
