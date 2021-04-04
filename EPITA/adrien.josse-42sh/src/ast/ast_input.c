#include <err.h>
#include <stddef.h>
#include <string.h>

#include "ast/ast_input.h"

#include "utils/memory.h"

#include "parser/parser_input.h"
#include "parser/command.h"

#include "ast/ast_command.h"
#include "ast/ast_utils.h"

void ast_input(struct input_node *input)
{
    if (!input)
        return;
    struct ast_printer *ast = xcalloc(1, sizeof(*ast));
    ast->dot = fopen("420sh.dot", "w+");
    fprintf(ast->dot,
        "digraph 420 {\n\
        node [fontname=\"%s\" fontsize=%d margin=\"%s\"]\n\
        node [shape=\"%s\"]\n",
        "monospace",    // fontname
        12,             // fontsize
        "0.3,0.1",      // margin
        "record"        // shape
    );

    ast_printer_add_node(ast, "input");
    int key = ast->key++;
    ast_printer_add_edge(ast, key);

    ast_list(input->list, ast);

    if (input->is_done)
        fprintf(ast->dot, "%d -> EOF\n", key);

    ast_printer_end(ast);
}

void ast_list(struct list_node *list, struct ast_printer *ast)
{
    struct and_or_node *cur = list->and_or;
    ast_printer_add_node(ast, "list");
    int key = ast->key++;
    while (cur)
    {
        ast_printer_add_edge(ast, key);
        ast_and_or(cur, ast);
        cur = cur->next;
    }
}

void ast_and_or(struct and_or_node *and_or, struct ast_printer *ast)
{
    struct pipeline_node *cur = and_or->pipeline;
    ast_printer_add_node(ast, "and_or");
    int key = ast->key++;
    ast_printer_add_edge(ast, key);
    ast_pipeline(cur, ast, 1);
    while (cur->next)
    {
        ast_printer_add_edge(ast, key);
        ast_pipeline(cur->next, ast, 0);
        cur = cur->next;
    }
}

void ast_pipeline(struct pipeline_node *pipeline,
                  struct ast_printer *ast,
                  int is_first)
{
    if (is_first)
        ast_printer_add_node(ast, "{|pipeline}");
    else if (pipeline->is_and)
        ast_printer_add_node(ast, "{&&|pipeline}");
    else
        ast_printer_add_node(ast, "{\\|\\||pipeline}");

    int key = ast->key++;
    struct command_node *cur = pipeline->command;
    while (cur)
    {
        ast_printer_add_edge(ast, key);
        ast_command(cur, ast);
        cur = cur->next;
    }
}
