/**
** \file
** Execution of the FUNCDEC NODE of the AST.
*/

#ifndef EXEC_FUNCDEC_H
# define EXEC_FUNCDEC_H

#include "input/env.h"

#include "parser/funcdec.h"

/**
** Function of addition of FUNCDEC NODE to the environment.
** @param funcdec The FUNCDEC NODE to add to the environment.
** @param env The execution environment.
** @return Returns 0.
*/
int add_funcdec(struct funcdec_node *funcdec, struct env *env);

/**
** Execution of the FUNCDEC NODE in AST.
** @param input The FUNCDEC NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_funcdec(struct env *env);

/**
** Clear the structure list of FUNCDEC NODE.
** @param funcs The list of FUNCDEC NODE to clear.
*/
void clear_funclist(struct funclist *funcs);

#endif /* ! EXEC_FUNCDEC_H */
