/**
** \file
** Freeing functions of the command nodes.
*/

#ifndef COMMAND_FREE_H
#define COMMAND_FREE_H

#include "parser/command.h"

/**
** Freeing of a SHELL COMMAND NODE.
** @param the SHELL COMMAND NODE to free.
*/
void shell_command_node_free(struct shell_command_node *shell_command);

/**
** Freeing of a COMMAND NODE.
** @param the COMMAND NODE to free.
*/
void command_node_free(struct command_node *node);

#endif // ! COMMAND_FREE_H
