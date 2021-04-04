/**
** \file
** Freeing functions of the simple command nodes.
*/

#ifndef SIMPLE_COMMAND_FREE_H
# define SIMPLE_COMMAND_FREE_H

#include "parser/simple_command.h"

/**
** Freeing of a PREFIX NODE.
** @param the PREFIX NODE to free.
*/
void prefix_node_free(struct prefix_node *nodes);

/**
** Freeing of a ELEMENT NODE.
** @param the ELEMENT NODE to free.
*/
void element_node_free(struct element_node *nodes);

/**
** Freeing of a SIMPLE COMMAND NODE.
** @param the SIMPLE COMMAND NODE to free.
*/
void simple_command_node_free(struct simple_command_node *node);

#endif /* ! SIMPLE_COMMAND_FREE_H */
