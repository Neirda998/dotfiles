#include "ast/ast_loops.h"

#include "parser/loops.h"

#include "ast/ast_compound_list.h"

void ast_rule_while(struct rule_while_node *rule_while,
                    struct ast_printer *ast)
{
    ast_printer_add_node(ast, "while");
    int key = ast->key++;

    ast_printer_add_edge(ast, key);
    ast_compound_list_break(rule_while->condition, ast);

    ast_printer_add_edge(ast, key);
    ast_compound_list_break(rule_while->body->body, ast);
}

void ast_rule_until(struct rule_until_node *rule_until,
                    struct ast_printer *ast)
{
    ast_printer_add_node(ast, "until");
    int key = ast->key++;

    ast_printer_add_edge(ast, key);
    ast_compound_list_break(rule_until->condition, ast);

    ast_printer_add_edge(ast, key);
    ast_compound_list_break(rule_until->body->body, ast);
}

void ast_rule_for(struct rule_for_node *rule_for, struct ast_printer *ast)
{
    int key = ast->key;

    fprintf(ast->dot, "\t%d [label=\"{for|",
        ast->key++
    );

    int i;
    for (i = 0; i < rule_for->size - 1; ++i)
        fprintf(ast->dot, "%s ", rule_for->iterated[i]);
    fprintf(ast->dot, "%s}\"]\n", rule_for->iterated[i]);

    ast_printer_add_edge(ast, key);
    ast_compound_list_break(rule_for->body->body, ast);
}
