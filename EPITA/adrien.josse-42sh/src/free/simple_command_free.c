#include <stdlib.h>

#include "free/simple_command_free.h"

#include "free/redirection_free.h"

void prefix_node_free(struct prefix_node *node)
{
    while (node)
    {
        struct prefix_node *tmp = node;
        node = node->next;
        if (tmp->type == Redirection)
            redirection_node_free(tmp->content.redirect);
        else
            free(tmp->content.word);
        free(tmp);
    }
}

void element_node_free(struct element_node *node)
{
    while (node)
    {
        struct element_node *tmp = node;
        node = node->next;
        if (tmp->type == Redirection)
            redirection_node_free(tmp->content.redirect);
        else
            free(tmp->content.word);
        free(tmp);
    }
}

void simple_command_node_free(struct simple_command_node *node)
{
    if (!node)
        return;

    prefix_node_free(node->prefixes);
    element_node_free(node->elements);
    free(node);
}
