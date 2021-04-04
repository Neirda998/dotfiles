/**
** \file
** \brief Lexer interface - Header.
*/

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

# include "built-in/built_in_alias.h"

# include "lexer/token.h"

# include "input/readline.h"

/**
** Main lexer structure to be used by parser.
** Contains :
** The currently lexed string,
** The current index in the lexed string,
** The list of aliases,
** The number of redirections in redirs,
** The list of heredocs on current line,
** The next token after index if already.
*/
struct lexer
{
    char *str;                ///< the currently lexed string.
    int idx;                  ///< the current index in the lexed string.

    struct aliases *aliases;  ///< the list of aliases.

    int here_idx;             ///< the number of redirections in redirs.
    char ***heredocs;         ///< the list of heredocs on current line.
    struct token *next_token; ///< the next token after index if already.
};

/**
** Lexer context initialisation function.
** @return Returns an allocated lexer containing the basic lexer context.
** This reads the first line of input.
*/
struct lexer *set_lexer(struct aliases *aliases);

/**
** Gets next token without eating word on input.
** @param lexer Current lexer context.
** @return Token corresponding to the next word on input.
*/
struct token *peek(struct lexer *lexer, int is_cmd);

/**
** Gets next token and eats next word on input.
** @param lexer Current lexer context.
** @param is_cmd Indicates a pop command case.
** @return Token corresponding to the next word on input.
*/
struct token *pop(struct lexer *lexer);

/**
** Gets next token and eats corresponding command on input.
** @param lexer Current lexer context.
** @return Token corresponding to the next command on input.
*/
struct token *pop_command(struct lexer *lexer);

/**
** Lexer context de-allocation function function.
** @param lexer Current lexer context to be freed.
*/
void unset_lexer(struct lexer *lexer);

#endif /* ! LEXER_H */
