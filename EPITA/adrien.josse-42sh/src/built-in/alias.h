/**
** \file
** Header for built-in operations alias's functions.
*/

#ifndef ALIAS_H
# define ALIAS_H

# include "input/env.h"

/**
** Init the list of aliases.
** @return Returns a new structure of aliases.
*/
struct aliases *new_aliases(void);

/**
** Create a new alias.
** @param name The name of the new alias.
** @param substitution The substitution string of the alias.
** @return Returns a new alias structure.
*/
struct alias *new_alias(char *name, char *substitution);

/**
** Resize the list of aliases.
** @param aliases The structure of aliases.
*/
void aliases_resize(struct aliases *aliases);

/**
** Insert a new alias in the aliases list.
** @param aliases The structure of aliases where to perform the insertion.
** @param alias The alias structure to insert.
*/
void aliases_insert(struct aliases *aliases, struct alias *alias);

/**
** Deletes an alias in the aliases list.
** @param aliases The structure of aliases where to perform the deletion.
** @param alias The alias structure to delete.
*/
void aliases_delete(struct aliases *aliases, int idx);

#endif /* ! ALIAS_H */
