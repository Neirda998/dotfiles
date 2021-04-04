#include <stdio.h>

#include "ast/ast_command.h"

#include "parser/command.h"
#include "parser/compound_list.h"
#include "parser/simple_command.h"

#include "ast/ast_case.h"
#include "ast/ast_funcdec.h"
#include "ast/ast_if.h"
#include "ast/ast_input.h"
#include "ast/ast_loops.h"
#include "ast/ast_redirection.h"
#include "ast/ast_utils.h"

void ast_command(struct command_node *command, struct ast_printer *ast)
{
    ast_printer_add_node(ast, "command");
    int key = ast->key++;
    if (command->simple_command)
    {
        ast_printer_add_edge(ast, key);
        ast_simple_command(command->simple_command, ast);
    }
    else
    {
        ast_printer_add_edge(ast, key);
        if (command->shell_command)
            ast_shell_command(command->shell_command, ast);
        else
            ast_funcdec(command->funcdec, ast);
        for (int i = 0; i < command->redir_len; i++)
        {
            ast_printer_add_edge(ast, key);
            ast_redirection(command->redirections[i], ast);
        }
    }
}

void ast_simple_command(struct simple_command_node *simple_command,
                        struct ast_printer *ast)
{
    ast_printer_add_node(ast, "simple_command");
    int key = ast->key++;
    // handle prefixes
    struct element_node *cur = simple_command->elements;
    while (cur)
    {
        ast_printer_add_edge(ast, key);
        if (cur->type == String)
        {
            fprintf(ast->dot, "\t%d [shape=Mrecord label=\"{element|%s}\"]\n",
                    ast->key++,
                    cur->content.word
            );
        }
        else
            ast_redirection(cur->content.redirect, ast);
        cur = cur->next;
    }
}

void ast_cmp_lst_brk(struct compound_list_break_node *list,
                     struct ast_printer *ast)
{
    ast_printer_add_node(ast, "compound_list");
    int key = ast->key++;
    struct and_or_node *cur = list->and_or_nodes;
    while (cur)
    {
        ast_printer_add_edge(ast, key);
        ast_and_or(cur, ast);
        cur = cur->next;
    }
}

void ast_cmp_lst(struct compound_list_node *list,
                 struct ast_printer *ast)
{
    ast_printer_add_node(ast, "compound_list");
    int key = ast->key++;
    struct and_or_node *cur = list->and_or_nodes;
    while (cur)
    {
        ast_printer_add_edge(ast, key);
        ast_and_or(cur, ast);
        cur = cur->next;
    }
}

void ast_shell_command(struct shell_command_node *shell_command,
                       struct ast_printer *ast)
{
    ast_printer_add_node(ast, "shell_command");
    int key = ast->key++;
    ast_printer_add_edge(ast, key);
    if (shell_command->type == CPD_LST_BRK)
        ast_cmp_lst_brk(shell_command->value.cpd_lst_brk, ast);
    else if (shell_command->type == CPD_LST)
        ast_cmp_lst(shell_command->value.cpd_lst, ast);
    else if (shell_command->type == RULE_IF)
        ast_rule_if(shell_command->value.rule_if, ast);
    else if (shell_command->type == RULE_WHILE)
        ast_rule_while(shell_command->value.rule_while, ast);
    else if (shell_command->type == RULE_UNTIL)
        ast_rule_until(shell_command->value.rule_until, ast);
    else if (shell_command->type == RULE_FOR)
        ast_rule_for(shell_command->value.rule_for, ast);
    else if (shell_command->type == RULE_CASE)
        ast_rule_case(shell_command->value.rule_case, ast);
}
