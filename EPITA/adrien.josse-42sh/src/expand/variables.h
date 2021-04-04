/**
** \file
** Header for variables managment.
*/

#ifndef VARIABLES_H
#define VARIABLES_H

#include "input/env.h"

/**
** The variable assignment structure.
*/
struct assignment
{
    char *name;  ///< the name of the variable.
    char *value; ///< the value of the variable.
};

/**
** Initialize a new variables structure.
** @return Returns the new allocated variables structure.
*/
struct vars *init_vars(void);

/**
** Set a new variable in the execution environment.
** @param env The execution environment.
** @param name The name of the variable.
** @param value The value of the variable.
** @return Returns the modified environment structure.
*/
struct env *set_value(struct env *env, char *name, char *value);
/**
** Get the value of the variable called name.
** @param env The execution environment.
** @param name The name of the variable.
** @return Returns the value of the variable, empty string if not found.
*/
char *get_value(struct env *env, const char *name);

/**
** Split an assignment word into a variable assignment structure.
** @param assign_word The assignment word to split.
** @param env The execution environment.
** @return Returns the new variable assignment structure.
*/
struct assignment *split_assign_word(char *assign_word, struct env *env);

#endif /* ! VARIABLES_H */
