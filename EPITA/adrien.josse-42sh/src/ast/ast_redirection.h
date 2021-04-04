/**
** \file
** Ast printing of redirections.
*/
#ifndef AST_REDIRECTION_H
# define AST_REDIRECTION_H

#include "parser/redirection.h"

#include "ast/ast_utils.h"

/**
** Adds a REDIR node to ast printer file.
** @param redir The REDIR node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_redirection(struct redirection_node *redir,
                     struct ast_printer *ast);

#endif /* ! AST_REDIRECTION_H */
