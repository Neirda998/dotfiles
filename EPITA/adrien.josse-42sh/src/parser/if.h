/**
** \file
** Grammar 'If' rule.
** Returns IF NODE for AST.
*/

#ifndef IF_H
# define IF_H

#include "lexer/lexer.h"

#include "parser/compound_list.h"

/**
** Else clause node structure.
** Contains :
** A condition that may be NULL,
** A clause body,
** Another optional else node.
*/
struct else_clause_node
{
    struct compound_list_break_node *condition; ///< optional elif condition.
    struct compound_list_break_node *body;      ///< body of else block.
    struct else_clause_node *next;              ///< optional else clause.
};

/**
** If rule node structure.
** Contains condition, if body and optional else node.
*/

struct rule_if_node
{
    struct compound_list_break_node *condition; ///< condition of if rule.
    struct compound_list_break_node *body;      ///< body of if block.
    struct else_clause_node *else_clause;       ///< optional else clause.
};

/**
** Creates IF NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns IF NODE for AST.
*/
struct else_clause_node *grammar_else_clause(struct lexer *lexer);

/**
** Creates IF NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns IF NODE for AST.
*/
struct rule_if_node *grammar_rule_if(struct lexer *lexer);

#endif /* ! IF_H */
