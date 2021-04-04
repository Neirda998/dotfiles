/**
** \file
** Ast printing of commands.
*/
#pragma once

#include "parser/command.h"

#include "ast/ast_utils.h"

/**
** Adds a COMMAND node to ast printer file.
** @param command The COMMAND node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_command(struct command_node *command, struct ast_printer *ast);

/**
** Adds a SIMPLE COMMAND node to ast printer file.
** @param simple_command The SIMPLE COMMAND node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_simple_command(struct simple_command_node *simple_command,
                        struct ast_printer *ast);

/**
** Adds a SHELL COMMAND node to ast printer file.
** @param shell_command The SHELL COMMAND node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_shell_command(struct shell_command_node *shell_command,
                       struct ast_printer *ast);
