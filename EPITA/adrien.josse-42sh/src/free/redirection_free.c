#include <stdlib.h>

#include "free/redirection_free.h"

void redirection_node_free(struct redirection_node *node)
{
    if (!node)
        return;

    free(node->redirect_out);
    free(node);
}
