#include "ast/ast_funcdec.h"

#include "parser/funcdec.h"

#include "ast/ast_utils.h"
#include "ast/ast_command.h"

void ast_funcdec(struct funcdec_node *func, struct ast_printer *ast)
{
    int key = ast->key;
    fprintf(ast->dot, "\t%d [label=\"{function|%s}\"]\n",
        ast->key++,
        func->name
    );

    ast_printer_add_edge(ast, key);
    ast_shell_command(func->body, ast);
}
