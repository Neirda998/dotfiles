/**
** \file
** Contains the environment of the shell.
*/

#ifndef ENV_H
# define ENV_H

#include "input/option.h"

/**
** The variable structure as a linked list.
** Contains :
** A string name,
** A string value,
** A pointer to the next variable.
*/
struct var
{
    char *name;       ///< the name of the variable.
    char *value;      ///< the value of the variable.

    struct var *next; ///< the next variable.
};

/**
** The list of variables structure.
** Contains :
** The length of the list,
** The first element of the linked list.
*/
struct vars
{
    int len;          ///< the length of the list.
    struct var *head; ///< the first element of the linked list.
};

/**
** The structure of an alias.
** Contains :
** The name of the alias,
** The substitution string of the alias.
*/
struct alias
{
    char *name;         ///< the name of the alias.
    char *substitution; ///< the substitution string of the alias.
};

/**
** The structure of aliases.
** Contains :
** The list of aliases,
** The size of the list,
** The capacity of the list.
*/
struct aliases
{
    struct alias **data; ///< the list of aliases.
    int size;            ///< the size of the list.
    int capacity;        ///< the capacity of the list.
};

/**
** The backup structure of the file descriptors as linked list.
** Contains :
** The original file descriptor,
** The new file descriptor,
** The backup of the old file descriptor,
** The next fd_backup structure.
*/
struct fd_backup
{
    int old_fd;             ///< the original file descriptor.
    int new_fd;             ///< the new file descriptor.
    int backup_fd;          ///< the backup of the old file descriptor.
    struct fd_backup *next; ///< the next fd_backup structure.
};

/**
** The linked list of functions.
** Contains :
** The current stored FUNCDEC NODE,
** The next element of the list.
*/
struct funclist
{
    struct funclist *next;     ///< the next element of the list.

    struct funcdec_node *node; ///< the current stored FUNCDEC NODE.
};

/**
** Shell environment structure.
** Contains :
** The environment options,
** The arguments of the current execution,
** The size of the args array,
** The list of variables,
** The list of declared functions,
** The backup structure of file descriptors,
** The arguments of a command execution,
** The list of aliases,
** The depth of loops,
** The number of loops to break,
** The number of loops to continue.
*/
struct env
{
    struct opt *opts;        ///< the environment options.

    char **args;             ///< the argument of current execution.
    int args_size;           ///< the size of the args array.

    struct vars *vars;       ///< the list of variables.

    char **env_vars;         ///< Array containing the value of called env vars.
    int env_vars_size;       ///< Size of the env_vars array.
    struct funclist *funcs;  ///< the list of declared functions.

    struct fd_backup *table; ///< the backup structure of file descriptors.

    char **argv;             ///< the arguments of a command execution.

    struct aliases *aliases; ///< the list of aliases.

    int loops_depth;         ///< the depth of loops.
    int nb_breaks;           ///< the number of loops to break.
    int nb_continues;        ///< the number of loops to continue.
};

/**
** Initializes the environment structure.
** @param argc The length of argv.
** @param argv The vector of arguments.
** @return Returns the new environment structure.
*/
struct env *init_env(int argc, char **argv);

/**
** Frees an environment structure.
** @param env The environment structure to free.`
*/
void env_free(struct env *env);

#endif /* ! ENV_H */
