/**
** \file
** Execution of the different compound list nodes of the AST.
** Execution of the COMPOUND LIST NODE.
** Execution of the COMPOUND LIST BREAK NODE.
*/

#ifndef EXEC_COMPOUND_LIST_H
#define EXEC_COMPOUND_LIST_H

#include "input/env.h"

#include "parser/compound_list.h"

/**
** Execution of the COMPOUND LIST NODE in AST.
** @param cmp_lst The COMPOUND LIST NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_compound_list(struct compound_list_node *cmp_lst, struct env *env);

/**
** Execution of the COMPOUND LIST BREAK NODE in AST.
** @param cmp_lst_brk The COMPOUND LIST BREAK NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_compound_list_break(struct compound_list_break_node *cmp_lst_brk,
                             struct env *env);

#endif /* ! EXEC_COMPOUND_LIST_H */
