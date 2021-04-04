#include <ctype.h>
#include <err.h>
#include <stddef.h>
#include <string.h>

#include "parser/simple_command.h"

#include "utils/memory.h"

#include "lexer/token.h"

#include "free/simple_command_free.h"

static void add_prefix(struct simple_command_node *command_node,
                       struct prefix_node *node)
{
    if (!command_node->prefixes)
        command_node->prefixes = node;
    else
    {
        struct prefix_node *head = command_node->prefixes;
        while (head->next)
            head = head->next;
        head->next = node;
    }
}

static void add_element(struct simple_command_node *command_node,
                        struct element_node *node)
{
    if (!command_node->elements)
        command_node->elements = node;
    else
    {
        struct element_node *head = command_node->elements;
        while (head->next)
            head = head->next;
        head->next = node;
    }
}

struct prefix_node *grammar_prefix(struct lexer *lexer)
{
    struct prefix_node *node = xcalloc(1, sizeof(struct prefix_node));

    struct token *token = peek(lexer, 0);
    if (token->type != WORD || !strchr(token->value.str, '='))
    {
        node->content.redirect = grammar_redirection(lexer);
        node->type = Redirection;
        if (!node->content.redirect)
        {
            prefix_node_free(node);
            return NULL;
        }
    }
    else
    {
        node->content.word = strdup(token->value.str);
        node->type = String;
        token_free(pop(lexer));
    }

    return node;
}

struct element_node *grammar_element(struct lexer *lexer)
{
    struct element_node *node = xcalloc(1, sizeof(struct element_node));

    struct token *token = peek(lexer, 1);
    if (token->type != WORD)
    {
        node->content.redirect = grammar_redirection(lexer);
        node->type = Redirection;
        if (!node->content.redirect)
        {
            element_node_free(node);
            return NULL;
        }
    }
    else
    {
        node->content.word = token->value.str ?
                             strdup(token->value.str) : NULL;
        node->type = String;
        token_free(pop(lexer));
    }

    return node;
}

struct simple_command_node *grammar_simple_command(struct lexer *lexer)
{
    struct simple_command_node *simple_command = xcalloc(1,
                                sizeof(struct simple_command_node));
    struct prefix_node *pref;
    while ((pref = grammar_prefix(lexer)))
        add_prefix(simple_command, pref);

    struct element_node *elt;
    while ((elt = grammar_element(lexer)))
        add_element(simple_command, elt);

    if (!simple_command->prefixes && !simple_command->elements)
    {
        simple_command_node_free(simple_command);
        return NULL;
    }
    return simple_command;
}
