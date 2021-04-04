#include "ast/ast_case.h"

#include "ast/ast_compound_list.h"

static void ast_rule_item(struct case_item_node *item, struct ast_printer *ast)
{
    int key = ast->key;
    fprintf(ast->dot, "\t%d [label=\"{case item|",
        ast->key++
    );
    int i;
    for (i = 0; i < item->size - 1; ++i)
        fprintf(ast->dot, "%s\\|", item->patterns[i]);
    fprintf(ast->dot, "%s}\"]\n", item->patterns[i]);
    ast_printer_add_edge(ast, key);
    ast_compound_list(item->statement, ast);
    if (item->next)
        ast_printer_add_edge(ast, key);
}

void ast_rule_case(struct rule_case_node *rule_case, struct ast_printer *ast)
{
    int key = ast->key;
    fprintf(ast->dot, "\t%d [label=\"{case|%s}\"]\n",
        ast->key++,
        rule_case->expression
    );
    ast_printer_add_edge(ast, key);

    struct case_item_node *cur = rule_case->case_clause->case_item;
    while (cur)
    {
        ast_rule_item(cur, ast);
        cur = cur->next;
    }
}
