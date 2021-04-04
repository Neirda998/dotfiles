/**
** \file
** Execution of the different command nodes of the AST.
** Execution of the COMMAND NODE.
** Execution of the SIMPLE COMMAND NODE.
** Execution of the SHELL COMMAND NODE.
*/

#pragma once

#include "input/env.h"

#include "parser/command.h"

/**
** Execution of a vector of strings.
** @param argv The vector of strings to execute.
** @return Returns the error code of the execution.
*/
int execute(char **argv);

/**
** Execution of a COMMAND NODE in an AST.
** @param command The COMMAND NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_command(struct command_node *command, struct env *env);

/**
** Execution of a SHELL COMMAND NODE in an AST.
** @param shell_command The SHELL COMMAND NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_shell_command(struct shell_command_node *shell_command,
                       struct env *env);
