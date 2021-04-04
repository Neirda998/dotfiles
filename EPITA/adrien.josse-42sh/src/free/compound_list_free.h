/**
** \file
** Freeing functions of the compound list nodes.
*/

#ifndef COMPOUND_LIST_FREE_H
#define COMPOUND_LIST_FREE_H

#include "parser/compound_list.h"

/**
** Freeing of a COMPOUND LIST NODE.
** @param the COMPOUND LIST NODE to free.
*/
void compound_list_node_free(struct compound_list_node *node);

/**
** Freeing of a COMPOUND LIST BREAK NODE.
** @param the COMPOUND LIST BREAK NODE to free.
*/
void compound_list_break_node_free(struct compound_list_break_node *node);

#endif // ! COMPOUND_LIST_FREE_H
