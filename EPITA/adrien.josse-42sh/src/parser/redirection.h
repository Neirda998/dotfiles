/**
** \file
** Grammar 'redirection', 'prefix' and 'element' rules.
*/

#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "lexer/lexer.h"
#include "lexer/token.h"

/**
** Redirection node structure.
** Contains an ionumber, the redirection operator and the redirection output.
*/
struct redirection_node
{
    int ionumber;           ///< input of redirection.⇧
    enum operator_value op; ///< operator value of redirection.
    int expand;             ///< indicator for here doc expansion.
    char *redirect_out;     ///< output of redirection.
};

/**
** Creates REDIRECTION NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns REDIRECTION NODE for AST.
*/
struct redirection_node *grammar_redirection(struct lexer *lexer);

#endif /* ! REDIRECTION_H */
