/**
** \file
** Ast printing of function declarations.
*/
#ifndef AST_FUNDEC_H
# define AST_FUNCDEC_H

#include "parser/funcdec.h"

#include "ast/ast_utils.h"

/**
** Adds a FUNDEC node to ast printer file.
** @param func The FUNCDEC node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_funcdec(struct funcdec_node *func, struct ast_printer *ast);

#endif /* ! AST_FUNCDEC_H */
