/**
** \file
** Execution of the simple command parts of the AST.
*/

#ifndef EXEC_SIMPLE_COMMAND_H
# define EXEC_SIMPLE_COMMAND_H

#include "parser/simple_command.h"

#include "exec/exec_redirection.h"

/**
** Execution of a PREFIX NODE in an AST.
** @param prefix The PREFIX NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_prefix(struct prefix_node *prefix, struct env *env);

/**
** Execution of a vector of words of a NODE in an AST.
** @param argv The vector of strings to execute.
** @return Returns the error code of the execution.
*/
int execute(char **argv);

/**
** Execution of an ELEMENT NODE in an AST.
** @param prefix The ELEMENT NODE to execute.
** @param idx The index of the argv environment vector to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_element(struct element_node *element,
                 int *idx, struct env *env);

/**
** Execution of a SIMPLE COMMAND NODE in an AST.
** @param simple_command The SIMPLE COMMAND NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_simple_command(struct simple_command_node *simple_command,
                        struct env *env);

#endif /* ! EXEC_SIMPLE_COMMAND_H */
