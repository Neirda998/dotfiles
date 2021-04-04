/**
** \file
** \brief Grammar 'Case' rules.
** Builds RULE CASE subtree for AST - header
*/

#ifndef CASE_H
# define CASE_H

#include "lexer/lexer.h"

#include "parser/compound_list.h"

/**
** Case rule node structure.
** Contains an expression and an optional CASE CLAUSE NODE.
*/
struct rule_case_node
{
    char *expression;
    struct case_clause_node *case_clause;
};

/**
** Case clause node structure.
** Contains a linked list of CASE ITEM NODE.
*/
struct case_clause_node
{
    struct case_item_node *case_item;
};

/**
** Case item node structure.
** Contains a PATTERNS array of at least one WORD element.
*/
struct case_item_node
{
    struct case_item_node *next;

    char **patterns;
    int size;
    struct compound_list_node *statement;
};

/**
** Creates RULE CASE NODE to add to AST.
** @param lexer The lexer structure.
** @return Returns RULE CASE NODE for AST.
*/
struct rule_case_node *grammar_rule_case(struct lexer *lexer);

/**
** Creates CASE CLAUSE NODE to add to AST.
** @param lexer The lexer structure.
** @return Returns CASE CLAUSE NODE for AST.
*/
struct case_clause_node *grammar_case_clause(struct lexer *lexer);

/**
** Creates CASE ITEM NODE to add to AST.
** @param lexer The lexer structure.
** @return Returns CASE ITEM NODE for AST.
*/
struct case_item_node *grammar_case_item(struct lexer *lexer);

#endif /* ! CASE_H */
