/**
** \file
** Execution of the loops nodes of the AST.
*/

#ifndef EXEC_LOOPS_H
# define EXEC_LOOPS_H

#include "input/env.h"

#include "parser/loops.h"

/**
** Execution of the RULE WHILE NODE in AST.
** @param rule_while The RULE WHILE NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_rule_while(struct rule_while_node *rule_while, struct env *env);

/**
** Execution of the RULE UNTIL NODE in AST.
** @param rule_until The RULE UNTIL NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_rule_until(struct rule_until_node *rule_until, struct env *env);

/**
** Execution of the RULE FOR NODE in AST.
** @param rule_for The RULE FOR NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_rule_for(struct rule_for_node *rule_for, struct env *env);

#endif /* ! EXEC_LOOPS_H */
