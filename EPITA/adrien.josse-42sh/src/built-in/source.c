#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/parser_input.h"

#include "expand/variables.h"

#include "utils/memory.h"
#include "free/parser_input_free.h"

#include "exec/exec_input.h"

#include "built-in/source.h"

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

static int file_exists(char *path)
{
    FILE *test = fopen(path, "r");
    if (!test)
        return 0;
    fclose(test);
    return 1;
}

static void launch_file(char *str, struct env *env)
{
    // backup args
    char **args_backup = xcalloc(env->args_size, sizeof(char *));
    int backup_size = 0;
    args_backup = copy_array(args_backup, &backup_size,
                             env->args, &env->args_size);

    // set function args
    for (int i = 1; env->argv[i]; i++)
    {
        env->args = xrealloc(env->args, sizeof(char *) * (env->args_size + 1));
        env->args[env->args_size] = strdup(env->argv[i]);
        env->args_size++;
    }

    FILE *rl_backup = rl_instream;
    if (!file_exists(str))
        return;
    rl_instream = open_input(0, str);
    struct lexer *lexer = set_lexer(env->aliases);
    struct input_node *ast = grammar_input(lexer);

    for (int i = 0; env->argv[i]; i++)
        free(env->argv[i]);
    free(env->argv);

    while (ast && !ast->is_done)
    {
        exec_input(ast, env);
        unset_lexer(lexer);
        lexer = set_lexer(env->aliases);
        input_node_free(ast);
        ast = grammar_input(lexer);
    }
    exec_input(ast, env);
    input_node_free(ast);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;


    env->args = copy_array(env->args, &env->args_size,
                           args_backup, &backup_size);

    // restore args
    free(args_backup);
}

int builtin_source(struct env *env)
{
    launch_file(env->argv[1], env);
    return atoi(get_value(env, "?"));
}
