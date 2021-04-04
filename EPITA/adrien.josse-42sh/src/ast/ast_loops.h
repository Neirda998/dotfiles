/**
** \file
** Ast printing of loops.
*/
#ifndef AST_LOOPS_H
# define AST_LOOPS_H

#include "parser/loops.h"

#include "ast/ast_utils.h"

/**
** Adds a RULE WHILE node to ast printer file.
** @param rule_while_node The RULE WHILE node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_rule_while(struct rule_while_node *rule_while,
                    struct ast_printer *ast);

/**
** Adds a RULE UNTIL node to ast printer file.
** @param rule_until_node The RULE WHILE node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_rule_until(struct rule_until_node *rule_until,
                    struct ast_printer *ast);

/**
** Adds a RULE FOR node to ast printer file.
** @param rule_for The RULE FOR node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_rule_for(struct rule_for_node *rule_for, struct ast_printer *ast);

#endif /* ! AST_LOOPS_H */
