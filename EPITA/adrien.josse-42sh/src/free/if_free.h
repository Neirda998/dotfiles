/**
** \file
** Freeing functions of the if nodes.
*/

#ifndef IF_FREE_H
#define IF_FREE_H

#include "parser/if.h"

/**
** Freeing of a RULE IF NODE.
** @param the RULE IF NODE to free.
*/
void rule_if_node_free(struct rule_if_node *if_node);

/**
** Freeing of a ELSE CLAUSE NODE.
** @param the ELSE CLAUSE NODE to free.
*/
void else_clause_node_free(struct else_clause_node *else_clause);

#endif /* ! IF_FREE_H */
