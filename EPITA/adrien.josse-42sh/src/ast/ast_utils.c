#include <stdio.h>
#include <stdlib.h>

#include "ast/ast_utils.h"

#include "utils/memory.h"

void ast_printer_add_node(struct ast_printer *ast, char *name)
{
    fprintf(ast->dot, "\t%d [label=\"%s\"]\n", ast->key, name);
}

void ast_printer_add_edge(struct ast_printer *ast, int key)
{
    fprintf(ast->dot, "\t%d -> %d\n", key, ast->key);
}

void ast_printer_end(struct ast_printer *ast)
{
    fprintf(ast->dot, "}\n");
    fclose(ast->dot);
    free(ast);
}
