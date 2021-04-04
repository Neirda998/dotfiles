#include <stdlib.h>

#include "free/compound_list_free.h"

#include "free/parser_input_free.h"

void compound_list_node_free(struct compound_list_node *node)
{
    if (!node)
        return;

    and_or_node_free(node->and_or_nodes);
    free(node);
}

void compound_list_break_node_free(struct compound_list_break_node *node)
{
    if (!node)
        return;

    and_or_node_free(node->and_or_nodes);
    free(node);
}
