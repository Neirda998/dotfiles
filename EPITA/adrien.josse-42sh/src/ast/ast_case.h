/**
** \file
** Ast printing of case rules.
*/
#ifndef AST_CASE_H
# define AST_CASE_H

#include "parser/case.h"

#include "ast/ast_utils.h"

/**
** Adds a RULE CASE node to ast printer file.
** @param rule_case The RULE CASE node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_rule_case(struct rule_case_node *rule_case, struct ast_printer *ast);

#endif /* ! AST_CASE_H */
