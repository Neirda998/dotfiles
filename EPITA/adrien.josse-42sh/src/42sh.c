#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>
#include <stdlib.h>

#include "utils/memory.h"

#include "input/option.h"
#include "input/input.h"
#include "input/env.h"

#include "lexer/lexer.h"

#include "parser/parser_input.h"

#include "ast/ast_input.h"

#include "expand/expand.h"
#include "expand/variables.h"

#include "free/parser_input_free.h"

#include "exec/exec_input.h"
#include "exec/main_utils.h"

#include "history/history.h"

static int file_exists(char *path)
{
    FILE *test = fopen(path, "r");
    if (!test)
        return 0;
    fclose(test);
    return 1;
}

static void int_handler(int status)
{
    if (status == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

static int uninteractive(char **argv, struct env *env)
{
    FILE *rl_backup = rl_instream;
    if (env->opts->is_c)
        rl_instream = open_input(1, env->opts->c_string);
    else
        rl_instream = open_input(0, argv[env->opts->index]);
    int ret = run_in_stream(env);
    close_input(rl_instream);
    env_free(env);
    rl_instream = rl_backup;
    return ret;
}

static void load_resource_file(char *str, struct env *env)
{
    FILE *rl_backup = rl_instream;
    if (!file_exists(str))
        return;
    rl_instream = open_input(0, str);
    run_in_stream(env);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

int main(int argc, char **argv)
{
    char name[4096];
    int ret = 0;
    struct env *env = init_env(argc, argv);

    struct lexer *lexer = NULL;
    struct input_node *ast = NULL;
    load_history();
    if (!env->opts->is_norc)
    {
        load_resource_file("/etc/42shrc", env);
        sprintf(name, "%s/.42shrc", getenv("HOME"));
        load_resource_file(name, env);
    }
    load_history();
    if (env->opts->is_c || file_exists(argv[env->opts->index]))
        return uninteractive(argv, env);
    else
    {
        while (1)
        {
            signal(SIGINT, int_handler);
            lexer = set_lexer(env->aliases);
            if (!lexer || lexer->str == NULL)
            {
                if (ast)
                    input_node_free(ast);
                ast = NULL;
                unset_lexer(lexer);
                lexer = NULL;
                break;
            }
            else
            {
                write_line_history(lexer->str);
                ast = grammar_input(lexer);
                if (!ast)
                    ret = 2;
                else if (ast->is_done)
                    ret = exec_input(ast, env);
                while (ast && !ast->is_done)
                {
                    if (lexer->here_idx)
                        peek(lexer, 0);
                    ret = exec_input(ast, env);
                    unset_lexer(lexer);
                    lexer = set_lexer(env->aliases);
                    write_line_history(lexer->str);
                    input_node_free(ast);
                    ast = grammar_input(lexer);
                }
                if (env->opts->is_ast_print)
                    ast_input(ast);
                input_node_free(ast);
                ast = NULL;
                unset_lexer(lexer);
            }
        }
    }
    save_history();
    if (lexer)
        unset_lexer(lexer);
    env_free(env);
    return ret;
}
