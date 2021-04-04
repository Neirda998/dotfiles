/**
** \file
** Ast printing of if / else rules.
*/
#ifndef AST_IF_H
#define AST_IF_H

#include "parser/if.h"

#include "ast/ast_utils.h"

/**
** Adds a ELSE node to ast printer file.
** @param else_clause The ELSE CLAUSE node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_else_clause(struct else_clause_node *else_clause,
                     struct ast_printer *ast);

/**
** Adds a RULE IF node to ast printer file.
** @param rule_if The RULE IF node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_rule_if(struct rule_if_node *rule_if,
                 struct ast_printer *ast);

#endif // ! AST_IF_H
