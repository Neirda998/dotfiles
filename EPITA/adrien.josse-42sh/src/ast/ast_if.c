#include "ast/ast_if.h"

#include "ast/ast_compound_list.h"

void ast_else_clause(struct else_clause_node *else_clause,
                     struct ast_printer *ast)
{
    int key;
    if (else_clause->condition)
    {
        ast_printer_add_node(ast, "elif");
        key = ast->key++;

        ast_printer_add_edge(ast, key);
        ast_compound_list_break(else_clause->condition, ast);
        if (else_clause->next)
        {
            ast_printer_add_edge(ast, key);
            ast_else_clause(else_clause->next, ast);
        }
    }
    else
    {
        ast_printer_add_node(ast, "else");
        key = ast->key++;
    }

    ast_printer_add_edge(ast, key);
    ast_compound_list_break(else_clause->body, ast);
}

void ast_rule_if(struct rule_if_node *rule_if,
                 struct ast_printer *ast)
{
    ast_printer_add_node(ast, "if");
    int key = ast->key++;

    ast_printer_add_edge(ast, key);
    ast_compound_list_break(rule_if->condition, ast);

    ast_printer_add_edge(ast, key);
    ast_compound_list_break(rule_if->body, ast);

    if (rule_if->else_clause)
    {
        ast_printer_add_edge(ast, key);
        ast_else_clause(rule_if->else_clause, ast);
    }
}
