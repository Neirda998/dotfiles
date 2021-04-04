#include <stdlib.h>
#include <string.h>

#include "exec/exec_command.h"
#include "exec/exec_funcdec.h"

#include "utils/memory.h"
#include "free/funcdec_free.h"

int add_funcdec(struct funcdec_node *funcdec, struct env *env)
{
    if (!env->funcs)
    {
        env->funcs = xcalloc(1, sizeof(struct funclist));
        env->funcs->node = funcdec;
    }
    else
    {
        struct funclist *new = xcalloc(1, sizeof(struct funclist));
        new->next = env->funcs;
        env->funcs = new;
    }

    return 0;
}

/**
** Search for a function in the environment.
** @param name The name of the function to search.
** @param env The execution environment.
** @return Returns the FUNCDEC NODE searched, NULL if not found.
*/
static struct funcdec_node *search_funcdec(struct env *env, char *name)
{
    struct funclist *cur = env->funcs;
    while (cur)
    {
        if (strcmp(cur->node->name, name) == 0)
            return cur->node;
        cur = cur->next;
    }
    return NULL;
}

/**
** Copies content of string array into destination.
** Empties both arrays in the process, but does not free the pointers.
** @param dst Destination array.
** @param size_dst Size of destination array.
** @param src Source array.
** @param size_src Size of source array.
** @return Pointer to destiation array.
*/
static char **copy_array(char **dst, int *size_dst, char **src, int *size_src)
{
    for (int i = 0; i < *size_dst; i++)
        free(dst[i]);
    *size_dst = 0;
    for (int i = 0; i < *size_src; i++)
    {
        dst = xrealloc(dst, sizeof(char *) * (*size_dst + 1));
        dst[i] = strdup(src[i]);
        free(src[i]);
        *size_dst += 1;
    }
    *size_src = 0;
    return dst;
}

int exec_funcdec(struct env *env)
{
    // backup args
    char **args_backup = xcalloc(env->args_size, sizeof(char *));
    int backup_size = 0;
    args_backup = copy_array(args_backup, &backup_size,
                             env->args, &env->args_size);

    // set function args
    for (int i = 0; env->argv[i]; i++)
    {
        env->args = xrealloc(env->args, sizeof(char *) * (env->args_size + 1));
        env->args[i] = strdup(env->argv[i]);
        env->args_size++;
    }

    int ret = 1;
    struct funcdec_node *funcdec = search_funcdec(env, env->argv[0]);
    if (funcdec)
    {
        for (int i = 0; env->argv[i]; i++)
            free(env->argv[i]);
        free(env->argv);
        ret = exec_shell_command(funcdec->body, env);
    }
    else
        ret = -1;

    env->args = copy_array(env->args, &env->args_size,
                           args_backup, &backup_size);

    // restore args
    free(args_backup);
    return ret;
}

void clear_funclist(struct funclist *funcs)
{
    while (funcs)
    {
        struct funclist *tmp = funcs;
        funcs = funcs->next;
        funcdec_node_free(tmp->node);
        free(tmp);
    }
    free(funcs);
}
