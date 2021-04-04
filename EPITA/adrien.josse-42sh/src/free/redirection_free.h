/**
** \file
** Freeing function of the redirection nodes.
*/

#ifndef REDIRECTION_FREE_H
#define REDIRECTION_FREE_H

#include "parser/redirection.h"

/**
** Freeing of a REDIRECTION NODE.
** @param the REDIRECTION NODE to free.
*/
void redirection_node_free(struct redirection_node *node);

#endif // ! REDIRECTION_FREE_H
