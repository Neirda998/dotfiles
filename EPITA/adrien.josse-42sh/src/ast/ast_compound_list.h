/**
** \file
** Ast printing of compound lists.
*/
#ifndef AST_COMPOUND_LIST_H
#define AST_COMPOUND_LIST_H

#include "parser/compound_list.h"

#include "ast/ast_utils.h"

/**
** Adds a COMPOUND LIST node to ast printer file.
** @param cmp_lst The COMPOUND LIST node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_compound_list(struct compound_list_node *cmp_lst,
                       struct ast_printer *ast);

/**
** Adds a COMPOUND LIST node to ast printer file.
** @param cmp_lst_brk The COMPOUND LIST node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_compound_list_break(struct compound_list_break_node *cmp_lst_brk,
                             struct ast_printer *ast);

#endif // ! AST_COMPOUND_LIST_H
