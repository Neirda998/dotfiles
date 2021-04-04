/**
** \file
** Execution of the RULE CASE NODE of the AST.
*/

#ifndef EXEC_CASE_H
# define EXEC_CASE_H

#include "input/env.h"

#include "parser/case.h"

/**
** Execute a RULE CASE NODE.
** @param rule_case The RULE CASE NODE to execute.
** @param env The execution environment
** @return Returns the error code of the execution.
*/
int exec_rule_case(struct rule_case_node *rule_case, struct env *env);

#endif /* ! EXEC_CASE_H */
