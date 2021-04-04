/**
** \file
** Ast printing of input.
*/
#ifndef AST_INPUT_H
#define AST_INPUT_H

#include <stddef.h>

#include "parser/command.h"
#include "parser/parser_input.h"

#include "ast/ast_utils.h"

/**
** Adds an INPUT node to ast printer file.
** @param input The INPUT node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_input(struct input_node *input);

/**
** Adds a LIST node to ast printer file.
** @param list The RULE CASE node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_list(struct list_node *list, struct ast_printer *ast);

/**
** Adds a AND OR node to ast printer file.
** @param and_or The AND OR node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_and_or(struct and_or_node *and_or, struct ast_printer *ast);

/**
** Adds a PIPELINE node to ast printer file.
** @param pipelinee The PIPELINE node from parser's ast.
** @param ast The ast printer struct.
*/
void ast_pipeline(struct pipeline_node *pipeline,
        struct ast_printer *ast,
        int is_first);

#endif /* ! AST_INPUT_H */
