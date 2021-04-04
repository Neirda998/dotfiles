#include <err.h>
#include <stddef.h>
#include <stdlib.h>

#include "parser/compound_list.h"

#include "utils/memory.h"

#include "lexer/token.h"

#include "parser/utils.h"
#include "parser/parser_input.h"

#include "free/compound_list_free.h"

struct compound_list_node *grammar_compound_list(struct lexer *lexer)
{
    struct compound_list_node *cpd_lst = xcalloc(1,
                                    sizeof(struct compound_list_node));

    skip_new_lines(lexer);

    cpd_lst->and_or_nodes = grammar_and_or(lexer);
    struct and_or_node *cur = cpd_lst->and_or_nodes;
    if (!cur)
    {
        free(cpd_lst);
        return NULL;
    }
    struct token *token = peek(lexer, 0);

    while (token->type == SEMI
           || token->type == AND
           || token->type == NEW_LINE)
    {
        token_free(pop(lexer));

        skip_new_lines(lexer);

        cur->next = grammar_and_or(lexer);
        if (!cur->next)
            break;
        cur = cur->next;
        token = peek(lexer, 0);
    }
    return cpd_lst;
}

struct compound_list_break_node *grammar_compound_list_break(
                                 struct lexer *lexer)
{
    struct compound_list_break_node *cpd_lst_brk = xcalloc(1,
                                    sizeof(struct compound_list_break_node));
    struct token *token = NULL;
    skip_new_lines(lexer);

    cpd_lst_brk->and_or_nodes = grammar_and_or(lexer);
    struct and_or_node *cur = cpd_lst_brk->and_or_nodes;
    if (!cur)
    {
        free(cpd_lst_brk);
        return NULL;
    }
    token = peek(lexer, 0);
    int found = 0;
    while (token->type == SEMI || token->type == AND
           || token->type == NEW_LINE)
    {
        found = 1;
        token_free(pop(lexer));

        skip_new_lines(lexer);

        cur->next = grammar_and_or(lexer);
        if (!cur->next)
            break;
        cur = cur->next;
        token = peek(lexer, 0);
    }
    if (!found)
    {
        compound_list_break_node_free(cpd_lst_brk);
        warnx("syntax error: expected ';' or '\n' or '&'");
        return NULL;
    }
    return cpd_lst_brk;
}
