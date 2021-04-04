/**
** \file
** Grammar 'Compound list' rules.
** Returns or a COMPOUND LIST NODE, or a COMPOUND LIST BREAK NODE for AST
*/

#ifndef COMPOUND_LIST_H
# define COMPOUND_LIST_H

#include "lexer/lexer.h"

#include "parser/parser_input.h"

/**
** Compound list node structure.
** Contains a list of and_or_nodes.
*/
struct compound_list_node
{
    struct and_or_node *and_or_nodes; ///< list of and_or_nodes
};

/**
** Compound list break node structure.
** Contains a list of and_or_nodes.
*/
struct compound_list_break_node
{
    struct and_or_node *and_or_nodes; ///< list of and_or_nodes
};

/**
** Creates COMPOUND LIST NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns COMPOUND LIST NODE for AST.
*/
struct compound_list_node *grammar_compound_list(struct lexer *lexer);

/**
** Creates COMPOUND LIST BREAK NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns COMPOUND LIST BREAK NODE for AST.
*/
struct compound_list_break_node *grammar_compound_list_break(
                                 struct lexer *lexer);

#endif /* ! COMPOUND_LIST_H */
