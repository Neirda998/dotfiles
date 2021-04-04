#include <err.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exec/exec_command.h"

#include "utils/fd_utils.h"
#include "utils/memory.h"

#include "input/env.h"
#include "parser/command.h"
#include "parser/simple_command.h"

#include "exec/exec_case.h"
#include "exec/exec_compound_list.h"
#include "exec/exec_funcdec.h"
#include "exec/exec_if.h"
#include "exec/exec_loops.h"
#include "exec/exec_redirection.h"
#include "exec/exec_simple_command.h"

#include "built-in/built_in.h"

int exec_command(struct command_node *command, struct env *env)
{
    if (!env->table)
        env->table = xcalloc(1, sizeof(struct fd_backup));
    for (int i = 0; i < command->redir_len; i++)
        if (exec_redirection(command->redirections[i], env) != 0)
            return 1;

    struct fd_backup *stacked = env->table;
    env->table = NULL;

    int ret = 1;
    if (command->simple_command)
        ret = exec_simple_command(command->simple_command, env);
    else if (command->shell_command)
        ret = exec_shell_command(command->shell_command, env);
    else
        ret = add_funcdec(command->funcdec, env);

    env->table = restore_fd_table(stacked);

    return ret;
}

int exec_shell_command(struct shell_command_node *shell_command,
                       struct env *env)
{
    if (shell_command->type == CPD_LST_BRK)
        return exec_compound_list_break(shell_command->value.cpd_lst_brk, env);
    else if (shell_command->type == CPD_LST)
        return exec_compound_list(shell_command->value.cpd_lst, env);
    else if (shell_command->type == RULE_FOR)
        return exec_rule_for(shell_command->value.rule_for, env);
    else if (shell_command->type == RULE_WHILE)
        return exec_rule_while(shell_command->value.rule_while, env);
    else if (shell_command->type == RULE_UNTIL)
        return exec_rule_until(shell_command->value.rule_until, env);
    else if (shell_command->type == RULE_CASE)
        return exec_rule_case(shell_command->value.rule_case, env);
    else // if (shell_command->type == RULE_IF)
        return exec_rule_if(shell_command->value.rule_if, env);
}
