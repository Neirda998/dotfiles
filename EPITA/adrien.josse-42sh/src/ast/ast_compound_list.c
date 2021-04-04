#include "ast/ast_compound_list.h"

#include "parser/compound_list.h"

#include "ast/ast_input.h"

void ast_compound_list(struct compound_list_node *cmp_lst,
                       struct ast_printer *ast)
{
    ast_printer_add_node(ast, "compound_list");
    int key = ast->key++;
    for (struct and_or_node *cur = cmp_lst->and_or_nodes; cur; cur = cur->next)
    {
        ast_printer_add_edge(ast, key);
        ast_and_or(cur, ast);
    }
}

void ast_compound_list_break(struct compound_list_break_node *cmp_lst_brk,
                             struct ast_printer *ast)
{

    ast_printer_add_node(ast, "compound_list");
    int key = ast->key++;
    for (struct and_or_node *cur = cmp_lst_brk->and_or_nodes; cur;
        cur = cur->next)
    {
        ast_printer_add_edge(ast, key);
        ast_and_or(cur, ast);
    }
}
