/**
** \file
** Grammar 'redirection', 'prefix' and 'element' rules.
*/

#ifndef SIMPLE_COMMAND_H
# define SIMPLE_COMMAND_H

#include "lexer/lexer.h"

#include "parser/redirection.h"

/**
** Type of the node.
** The node can be a redirection or a string that represents
** a WORD or ASSIGNMENT_WORD.
*/
enum node_type
{
    String = 0,
    Redirection
};

/**
** Content that can be used in a PREFIX NODE or an ELEMENT NODE.
** Contains a REDIRECTION NODE or a string content.
*/
union content
{
    struct redirection_node *redirect; ///< REDIRECTION NODE.
    char *word;                        ///< string content.
};

/**
** Prefix node structure.
** Contains the value of the prefix.
*/
struct prefix_node
{
    enum node_type type;      ///< type of the prefix.
    union content content;    ///< content of prefix.
    struct prefix_node *next; ///< the next prefix. Is NULL by default.
};

/**
** Element node structure.
** Contains the content of the element.
*/
struct element_node
{
    enum node_type type;       ///< type of the element.
    union content content;     ///< content of element.
    struct element_node *next; ///< the next element. Is NULL by default.
};

/**
** Simple command structure node.
** Contains a linked list of PREFIX NODE that can be NULL
** and a linked list of ELEMENT NODE that can be NULL.
** Both cannot be NULL at the same time.
*/
struct simple_command_node
{
    struct prefix_node *prefixes;  ///< linked list of PREFIX NODE.
    struct element_node *elements; ///< linked list of ELEMENT NODE.
};


/**
** Creates ELEMENT NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns ELEMENT NODE for AST.
*/
struct element_node *grammar_element(struct lexer *lexer);

/**
** Creates PREFIX NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns PREFIX NODE for AST.
*/
struct prefix_node *grammar_prefix(struct lexer *lexer);


/**
** Creates SIMPLE COMMAND NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns SIMPLE COMMAND NODE for AST.
*/
struct simple_command_node *grammar_simple_command(struct lexer *lexer);

#endif /* ! REDIRECTION_H */
