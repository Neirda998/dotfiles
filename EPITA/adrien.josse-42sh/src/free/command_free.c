#include <stdlib.h>

#include "free/command_free.h"

#include "free/case_free.h"
#include "free/compound_list_free.h"
#include "free/funcdec_free.h"
#include "free/if_free.h"
#include "free/loops_free.h"
#include "free/redirection_free.h"
#include "free/simple_command_free.h"

void shell_command_node_free(struct shell_command_node *shell_command)
{
    if (!shell_command)
        return;
    switch (shell_command->type)
    {
    case CPD_LST_BRK:
        compound_list_break_node_free(shell_command->value.cpd_lst_brk);
        break;
    case CPD_LST:
        compound_list_node_free(shell_command->value.cpd_lst);
        break;
    case RULE_FOR:
        rule_for_node_free(shell_command->value.rule_for);
        break;
    case RULE_WHILE:
        rule_while_node_free(shell_command->value.rule_while);
        break;
    case RULE_UNTIL:
        rule_until_node_free(shell_command->value.rule_until);
        break;
    case RULE_CASE:
        rule_case_node_free(shell_command->value.rule_case);
        break;
    case RULE_IF:
        rule_if_node_free(shell_command->value.rule_if);
        break;
    }
    free(shell_command);
}

void command_node_free(struct command_node *node)
{
    while (node)
    {
        struct command_node *tmp = node;
        node = node->next;
        simple_command_node_free(tmp->simple_command);
        shell_command_node_free(tmp->shell_command);
        // We do not free funced here since it's freed by the environment
        // funcdec_node_free(tmp->funcdec);
        for (int i = 0; i < tmp->redir_len; i++)
            redirection_node_free(tmp->redirections[i]);
        free(tmp->redirections);

        free(tmp);
    }
}
