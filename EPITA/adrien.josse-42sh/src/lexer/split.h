/**
** \file
** \brief Utilities for splitting - Header.
*/
#ifndef SPLIT_H
# define SPLIT_H

#include "lexer/lexer.h"

#include "lexer/quote_len.h"

/**
** Identifies and returns a word contained in quotes.
** @param lexer The lexer structure.
** @param quote The type of quote.
** @return Returns the word contained in quotes (quotes included).
*/
char *word_ambi_quotes(struct lexer *lexer, enum quote_type quote);

/**
** Returns next word to be lexed.
** If word is in between quotes return word surrounded by quotes.
** Calls get_next_line if nessecary (when handling quotes).
** @param str String to be lexed.
** @param idx Pointer to the current index.
** Returns next word to be lexed.
*/
char *next_word(struct lexer *lexer, int alias);

/**
** Returns next command to be lexed.
** If some word are in between quotes, quotes are included.
** Calls get_next_line if nessecary (when handling quotes).
** @param str String to be lexed.
** @param idx Pointer to the current index.
** Returns next command to be lexed.
*/
char *next_command(char *str, int *idx);

/**
** Checks if a given string is a redirection operator.
** @param key The string to test.
** @return Returns 1 if the string is a redirection, else 0.
*/
int is_redir_first(char *key);

#endif /* ! SPLIT_H */
