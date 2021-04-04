#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "exec/exec_simple_command.h"

#include "exec/exec_funcdec.h"

#include "utils/fd_utils.h"
#include "utils/memory.h"

#include "expand/variables.h"
#include "expand/expand.h"
#include "expand/variables.h"

#include "built-in/built_in.h"

int exec_prefix(struct prefix_node *prefix, struct env *env)
{
    if (prefix->type == String)
    {
        struct assignment *assignment = split_assign_word(prefix->content.word,
                                                          env);
        if (!assignment->value)
            assignment->value = strdup("");
        env = set_value(env, assignment->name, assignment->value);
        free(assignment);
    }
    else if (exec_redirection(prefix->content.redirect, env) != 0)
        return 1;
    return 0;
}

static void free_argv(char **argv)
{
    if (!argv)
        return;
    for (int idx = 0; argv[idx]; idx++)
        free(argv[idx]);
    free(argv);
}

int execute(char **argv)
{
    int pid = fork();

    if (!pid)
    {
        execvp(argv[0], argv);
        free_argv(argv);
        errx(127, "command not found.");
    }
    else
    {
        int wstatus;
        int wret = waitpid(pid, &wstatus, 0);
        free_argv(argv);
        return wret > 0 ? WEXITSTATUS(wstatus) : 0;
    }
}

int exec_element(struct element_node *element,
                 int *idx, struct env *env)
{
    if (element->type == String)
    {
        env->argv = xrealloc(env->argv, sizeof(char *) * (*(idx) + 1));
        env->argv[(*idx)] = strdup(element->content.word);
        (*idx)++;
    }
    else
    {
        if (exec_redirection(element->content.redirect, env) != 0)
            return 1;
    }
    env->argv = xrealloc(env->argv, sizeof(char *) * (*(idx) + 1));
    return 0;
}

int exec_simple_command(struct simple_command_node *simple_command,
                        struct env *env)
{
    int idx = 0;
    env->argv = NULL; //xcalloc(1, sizeof(char *) * 1);
    if (!env->table)
        env->table = xcalloc(1, sizeof(struct fd_backup));

    struct prefix_node *prefs = simple_command->prefixes;
    while (prefs)
    {
        int pref_ret = exec_prefix(prefs, env);
        if (pref_ret != 0)
            return 1;
        prefs = prefs->next;
    }

    struct element_node *cur = simple_command->elements;
    while (cur)
    {
        int elmt_ret = exec_element(cur, &idx, env);
        env->argv[idx] = NULL;
        if (elmt_ret != 0)
        {
            free_argv(env->argv);
            env->table = restore_fd_table(env->table);
            return 1;
        }
        cur = cur->next;
    }

    int ret = 0;
    if (env->argv)
    {
        int argc = get_argc(env->argv);
        env->argv = expand_words(env->argv, &argc, env);
        env->argv = xrealloc(env->argv, sizeof(char *) * (argc + 1));
        env->argv[argc] = NULL;
        int to_free = strcmp("source", env->argv[0]) != 0
                      && strcmp(".", env->argv[0]) != 0;
        if ((ret = exec_funcdec(env)) == -1)
        {
            if ((ret = exec_built_in(env)) == -1)
                ret = execute(env->argv);
            else if (to_free)
                free_argv(env->argv);
        }
    }
    env->table = restore_fd_table(env->table);

    return ret;
}
