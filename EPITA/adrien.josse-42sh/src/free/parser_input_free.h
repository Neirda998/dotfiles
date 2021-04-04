/**
** \file
** Freeing functions of the root nodes.
*/

#ifndef PARSER_INPUT_FREE_H
# define PARSER_INPUT_FREE_H

#include "parser/parser_input.h"

/**
** Freeing of a PIPELINE NODE.
** @param the PIPELINE NODE to free.
*/
void pipeline_node_free(struct pipeline_node *node);

/**
** Freeing of a AND_OR NODE.
** @param the AND_OR NODE to free.
*/
void and_or_node_free(struct and_or_node *node);

/**
** Freeing of LIST NODE.
** @param the LIST NODE to free.
*/
void list_node_free(struct list_node *list);

/**
** Freeing of a INPUT NODE as root of the AST.
** @param the INPUT NODE to free.
*/
void input_node_free(struct input_node *input_node);

#endif /* ! FREE_2_H */
