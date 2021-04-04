#include <stddef.h>
#include <err.h>
#include <stdlib.h>

#include "parser/parser_input.h"

#include "utils/memory.h"

#include "lexer/token.h"

#include "parser/utils.h"
#include "parser/command.h"

#include "free/parser_input_free.h"

struct input_node *grammar_input(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    struct input_node *input = xcalloc(1, sizeof(struct input_node));
    if (token->type == END_OF_FILE)
    {
        input->is_done = 1;
        return input;
    }
    else if (token->type == NEW_LINE)
    {
        input->is_done = 0;
        return input;
    }
    input->list = grammar_list(lexer);
    if (!input->list)
    {
        input_node_free(input);

        // No need for error message since :
        // already present in recursion bottom.
        warnx("syntax error: expected valid input");
        return NULL;
    }
    token = peek(lexer, 0);
    if (token->type == END_OF_FILE)
        input->is_done = 1;
    else if (token->type == NEW_LINE)
        input->is_done = 0;
    else
    {
        input_node_free(input);
        warnx("syntax error: expected EOF or \\n");
        return NULL;
    }
    token_free(pop(lexer));
    return input;
}

struct list_node *grammar_list(struct lexer *lexer)
{
    struct list_node *list = xcalloc(1, sizeof(struct list_node));
    list->and_or = grammar_and_or(lexer);
    if (!list->and_or)
    {
        list_node_free(list);
        return NULL;
    }
    struct and_or_node *cur = list->and_or;
    struct token *token = peek(lexer, 0);
    while (token->type == SEMI || token->type == AND)
    {
        cur->is_background = token->type == AND;
        token_free(pop(lexer));
        cur->next = grammar_and_or(lexer);
        if (!cur->next)
            break;
        cur = cur->next;
        token = peek(lexer, 0);
    }
    return list;
}

struct and_or_node *grammar_and_or(struct lexer *lexer)
{
    struct and_or_node *and_or = xcalloc(1, sizeof(struct and_or_node));
    and_or->pipeline = grammar_pipeline(lexer);
    struct pipeline_node *cur = and_or->pipeline;
    if (!cur)
    {
        and_or_node_free(and_or);
        return NULL;
    }
    struct token *token = peek(lexer, 0);
    while (token->type == OPERATOR &&
          (token->value.op == AND_IF || token->value.op == OR_IF))
    {
        int is_and = token->value.op == AND_IF;
        token_free(pop(lexer));

        skip_new_lines(lexer);

        cur->next = grammar_pipeline(lexer);
        if (!cur->next)
        {
            and_or_node_free(and_or);
            warnx("syntax error: expected pipeline after && or ||");
            return NULL;
        }
        cur->next->is_and = is_and;
        cur = cur->next;
        token = peek(lexer, 0);
    }
    return and_or;
}

struct pipeline_node *grammar_pipeline(struct lexer *lexer)
{
    struct pipeline_node *pipeline = xcalloc(1, sizeof(struct pipeline_node));
    struct token *token = peek(lexer, 0);
    if (token->type == RESERVED && token->value.res == Bang)
    {
        pipeline->is_not = 1;
        token_free(pop(lexer));
        token = peek(lexer, 0);
    }
    pipeline->command = grammar_command(lexer);
    struct command_node *cur = pipeline->command;
    if (!pipeline->command)
    {
        if (pipeline->is_not)
            return pipeline;
        pipeline_node_free(pipeline);
        return NULL;
    }
    token = peek(lexer, 0);
    while (token->type == OPERATOR && token->value.op == PIPE)
    {
        token_free(pop(lexer));

        skip_new_lines(lexer);

        cur->next = grammar_command(lexer);
        if (!cur->next)
        {
            pipeline_node_free(pipeline);
            warnx("syntax error: expected command after |");
            return NULL;
        }
        cur = cur->next;
        token = peek(lexer, 0);
    }
    return pipeline;
}
