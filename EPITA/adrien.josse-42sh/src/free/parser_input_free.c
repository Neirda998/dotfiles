#include <stdlib.h>

#include "free/command_free.h"
#include "free/parser_input_free.h"

void pipeline_node_free(struct pipeline_node *node)
{
    while (node)
    {
        struct pipeline_node *tmp = node;
        node = node->next;
        command_node_free(tmp->command);
        free(tmp);
    }
}

void and_or_node_free(struct and_or_node *node)
{
    while (node)
    {
        struct and_or_node *tmp = node;
        node = node->next;
        pipeline_node_free(tmp->pipeline);
        free(tmp);
    }
}

void list_node_free(struct list_node *list)
{
    if (!list)
        return;
    and_or_node_free(list->and_or);
    free(list);
}

void input_node_free(struct input_node *input_node)
{
    if(!input_node)
        return;
    list_node_free(input_node->list);
    free(input_node);
}
