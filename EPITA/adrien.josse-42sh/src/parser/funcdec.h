/**
** \file
** Grammar 'funcdec' rules.
**/

#ifndef FUNCDEC_H
# define FUNCDEC_H

#include "parser/command.h"

/**
** Funcdec structure node.
** Contains a name string and a struct shell_command_node.
*/
struct funcdec_node
{
    char *name;
    struct shell_command_node *body;
};

/**
** Creates a FUNCDEC NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns FUNCDEC NODE for AST.
*/
struct funcdec_node *grammar_funcdec(struct lexer *lexer);

#endif /* ! FUNCDEC_H */
