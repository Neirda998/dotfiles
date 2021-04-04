/**
** \file
** Header for built-in alias's function.
*/

#ifndef BUILT_IN_ALIAS_H
# define BUILT_IN_ALIAS_H

# include "input/env.h"

/**
** Search for an alias in the list of aliases
** @param aliases The list of aliases where the search is performed.
** @param name The name of the alias to search.
** @return Returns the index of the alias if found, -1 if not present.
*/
int alias_search(struct aliases *aliases, char *name);

/**
** Built-in function `alias`.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int builtin_alias(struct env *env);

/**
** Built-in function `unalias`.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int builtin_unalias(struct env *env);

/**
** The deletion function of all aliases.
** @param env The execution environment.
*/
void delete_aliases(struct env *env);

/**
** The expansion of an alias function.
** @param str The lexer string to expand.
** @param prev The string field to substitute.
** @param next The substitution string to apply.
** @param idx The lexer index.
** @return Returns the replaced string.
*/
char *alias_expand(char *str, char *prev, char *next, int idx);

#endif /* ! BUILT_IN_ALIAS_H */
