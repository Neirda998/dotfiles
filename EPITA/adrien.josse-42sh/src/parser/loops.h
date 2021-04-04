/**
** \file
** Grammar 'loops' rules.
** Returns an AST node corresponding to the loop asked (until, while, or for).
*/

#ifndef LOOPS_H
# define LOOPS_H

#include "lexer/lexer.h"

#include "parser/compound_list.h"

/**
** Do group node structure.
** Contains a compound_list_break.
*/
struct do_group_node
{
    struct compound_list_break_node *body; ///< compound_list_break.
};

/**
** For rule node structure.
** Contains an iterator string, a list of string for the iterated elements,
** and the execution body.
*/
struct rule_for_node
{
    char *iterator;             ///< iterator string.
    char **iterated;            ///< iterated strings.
    int size;                   ///< size of array 'iterated'.
    struct do_group_node *body; ///< body.
};

/**
** While rule node structure.
** Contains a compound list break for the condition,
** and a do group node for the execution body.
*/
struct rule_while_node
{
    struct compound_list_break_node *condition; ///< condition.
    struct do_group_node *body;                 ///< body.
};

/**
** Until rule node structure.
** Contains a compound list break for the condition,
** and a do group node for the execution body.
*/
struct rule_until_node
{
    struct compound_list_break_node *condition; ///< condition.
    struct do_group_node *body;                 ///< body.
};

/**
** Creates DO GROUP NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns DO GROUP NODE for AST.
*/
struct do_group_node *grammar_do_group(struct lexer *lexer);

/*
** Creates RULE WHILE NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns RULE WHILE NODE for AST.
*/
struct rule_while_node *grammar_rule_while(struct lexer *lexer);

/*
** Creates RULE UNTIL NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns RULE UNTIL NODE for AST.
*/
struct rule_until_node *grammar_rule_until(struct lexer *lexer);

/*
** Creates FOR NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns FOR NODE for AST.
*/
struct rule_for_node *grammar_rule_for(struct lexer *lexer);

#endif /* ! LOOPS_H */
