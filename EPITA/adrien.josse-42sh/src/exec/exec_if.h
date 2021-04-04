/**
** \file
** Execution of the if rules of the AST.
*/

#ifndef EXEC_IF_H
#define EXEC_IF_H

#include "input/env.h"

#include "parser/if.h"

/**
** Execution of the ELSE CLAUSE NODE in AST.
** @param else_clause The ELSE CLAUSE NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_else_clause(struct else_clause_node *else_clause, struct env *env);

/**
** Execution of the RULE IF NODE in AST.
** @param rule_if The RULE IF NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_rule_if(struct rule_if_node *rule_if, struct env *env);

#endif // ! EXEC_IF_H
