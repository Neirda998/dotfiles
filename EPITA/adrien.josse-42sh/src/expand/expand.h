/**
** \file
** Header for expansion functions.
*/

#ifndef EXPAND_H
# define EXPAND_H

#include "input/env.h"

/**
** Splitted word structure.
** Representation of a word that has been quote removed and field splitted.
*/
struct splitted
{
    char **split_words; ///< the list of splitted words.
    int size;           ///< the size of the list of splitted words.
};

/**
** Description
** @param word The word where to perform the expansion.
** @param env The execution environment.
** @param tilde_exp Boolean to know if a tilde expansion is required.
** @return Returns the expanded string.
*/
char *expand_vars(char *word, struct env *env, int tilde_exp);

/**
** The quote removal functions.
** @param word The string where to process the quote removal.
** @param quote The kind of quote to remove.
** @return Returns the quote removed string.
*/
char *remove_quotes(char *word);

/**
** The word expansion function.
** @param word The word to expand.
** @param env The execution environment.
** @param quote The kind of quote to remove.
** @return Returns
*/
char *expand_word(char *word, struct env *env);

/**
** Perform word expansion on the words array.
** @param words The list of words to expand.
** @param words_size The length of the words array.
** @param env The execution environment.
** @return Returns an array containing the new words of size words_size.
*/
char **expand_words(char **words, int *words_size, struct env *env);

#endif /* ! EXPAND_H */
