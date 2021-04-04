/**
** \file
** Execution of the redirection rules of the AST.
*/

#ifndef EXEC_REDIRECTION_H
# define EXEC_REDIRECTION_H

#include "input/env.h"

#include "parser/redirection.h"

/**
** Execution of a `<` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_less(struct redirection_node *redir, struct env *env);

/**
** Execution of a `>` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_great(struct redirection_node *redir, struct env *env);

/**
** Execution of a `<&` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_lessand(struct redirection_node *redir, struct env *env);

/**
** Execution of a `>&` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_greatand(struct redirection_node *redir, struct env *env);

/**
** Execution of a `>>` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_dgreat(struct redirection_node *redir, struct env *env);

/**
** Execution of a `>|` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_clobber(struct redirection_node *redir, struct env *env);

/**
** Execution of a `<>` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_lessgreat(struct redirection_node *redir,
                               struct env *env);
/**
** Execution of a `<<` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_dless(struct redirection_node *redir, struct env *env);

/**
** Execution of a `<<-` redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection_dlessdash(struct redirection_node *redir,
                               struct env *env);

/**
** Execution of a redirection.
** @param redir The redirection_node to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_redirection(struct redirection_node *redir, struct env *env);

#endif /* ! EXEC_REDIRECTION_H */
