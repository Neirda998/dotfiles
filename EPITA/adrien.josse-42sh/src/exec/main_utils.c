#include "main_utils.h"

#include "ast/ast_input.h"

#include "lexer/lexer.h"

#include "parser/parser_input.h"

#include "free/parser_input_free.h"

#include "exec/exec_input.h"

int run_in_stream(struct env *env)
{
    int ret = 0;
    struct lexer *lexer = set_lexer(env->aliases);
    struct input_node *ast = grammar_input(lexer);
    while (ast && !ast->is_done)
    {
        if (lexer->here_idx)
            peek(lexer, 0);
        ret = exec_input(ast, env);
        unset_lexer(lexer);
        lexer = set_lexer(env->aliases);
        input_node_free(ast);
        ast = grammar_input(lexer);
    }
    if (env->opts->is_ast_print)
        ast_input(ast);
    ret = exec_input(ast, env);
    unset_lexer(lexer);
    input_node_free(ast);
    return ret;
}
