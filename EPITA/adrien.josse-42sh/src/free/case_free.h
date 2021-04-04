/**
** \file
** Freeing functions of the case nodes.
*/

#ifndef CASE_FREE_H
#define CASE_FREE_H

#include "parser/case.h"

/**
** Freeing of a RULE CASE NODE.
** @param the RULE CASE NODE to free.
*/
void rule_case_node_free(struct rule_case_node *rule_case);

/**
** Freeing of a CASE CLAUSE NODE.
** @param the CASE CLAUSE NODE to free.
*/
void case_clause_node_free(struct case_clause_node *case_clause);

/**
** Freeing of a CASE ITEM NODE.
** @param the CASE ITEM NODE to free.
*/
void case_item_node_free(struct case_item_node *case_item);

#endif // ! CASE_FREE_H
