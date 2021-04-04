#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "input/env.h"

#include "built-in/built_in_alias.h"
#include "built-in/cd.h"
#include "built-in/echo.h"
#include "built-in/exit.h"
#include "history/history.h"
#include "built-in/continue.h"
#include "built-in/break.h"
#include "built-in/export.h"
#include "built-in/set.h"
#include "built-in/source.h"

int get_argc(char **argv)
{
    int argc = 0;
    if (!argv)
        return 0;
    while (argv[argc] != NULL)
        argc++;
    return argc;
}

static char *is_builtin(char *arg)
{
    char *built_ins[] =
    {
        "alias",
        "cd",
        "echo",
        "exit",
        "history",
        "continue",
        "break",
        "export",
        "set",
        "unalias",
        "source",
        "."
    };
    size_t size = sizeof(built_ins) / sizeof(char *);
    for (size_t i = 0; i < size; i++)
    {
        if (strcmp(built_ins[i], arg) == 0)
            return built_ins[i];
    }
    return NULL;
}

int exec_built_in(struct env *env)
{
    char **argv = env->argv;
    int argc = get_argc(argv);
    if (!is_builtin(argv[0]))
        return -1;

    if (strcmp(argv[0], "alias") == 0)
        return builtin_alias(env);
    if (strcmp(argv[0], "cd") == 0)
        return builtin_cd(argc, argv);
    if (strcmp(argv[0], "echo") == 0)
        return builtin_echo(argc, argv);
    if (strcmp(argv[0], "exit") == 0)
        return builtin_exit(argc, argv);
    if (strcmp(argv[0], "history") == 0)
        return builtin_history(argc, argv);
    if (strcmp(argv[0], "continue") == 0)
        return builtin_continue(env);
    if (strcmp(argv[0], "break") == 0)
        return builtin_break(env);
    if (strcmp(argv[0], "export") == 0)
        return builtin_export(argc, argv);
    if (strcmp(argv[0], "set") == 0)
        return builtin_set(env);
    if (strcmp(argv[0], "unalias") == 0)
        return builtin_unalias(env);
    if (strcmp(argv[0], "source") == 0 || strcmp(argv[0], ".") == 0)
        return builtin_source(env);

    return 0;
}
