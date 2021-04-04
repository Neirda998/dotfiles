/**
** \file
** Freeing functions of the loops nodes.
*/

#ifndef LOOPS_FREE_H
#define LOOPS_FREE_H

#include "parser/loops.h"

/**
** Freeing of the DO GROUP NODE.
** @param the DO GROUP NODE to free.
*/
void do_group_node_free(struct do_group_node *do_group);

/**
** Freeing of the RULE WHILE NODE.
** @param the RULE WHILE NODE to free.
*/
void rule_while_node_free(struct rule_while_node *rule_while);

/**
** Freeing of the RULE UNTIL NODE.
** @param the RULE UNTIL NODE to free.
*/
void rule_until_node_free(struct rule_until_node *rule_until);

/**
** Freeing of the RULE FOR NODE.
** @param the RULE FOR NODE to free.
*/
void rule_for_node_free(struct rule_for_node *rule_for);

#endif /* ! LOOPS_FREE_H */
