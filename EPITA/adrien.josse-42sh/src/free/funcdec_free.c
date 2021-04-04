#include <stdlib.h>

#include "free/funcdec_free.h"

#include "free/command_free.h"

void funcdec_node_free(struct funcdec_node *funcdec)
{
    if (!funcdec)
        return;

    free(funcdec->name);
    shell_command_node_free(funcdec->body);
    free(funcdec);
}
