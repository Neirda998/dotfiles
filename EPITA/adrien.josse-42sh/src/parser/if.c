#include <err.h>
#include <stddef.h>

#include "parser/if.h"

#include "utils/memory.h"

#include "lexer/token.h"

#include "free/if_free.h"

struct else_clause_node *grammar_else_clause(struct lexer *lexer)
{
    struct else_clause_node *else_clause =
        xcalloc(1, sizeof(struct else_clause_node));
    struct token *token = peek(lexer, 0);
    if (token->type == RESERVED && token->value.res == Else)
    {
        token_free(pop(lexer));
        else_clause->body = grammar_compound_list_break(lexer);
        return else_clause;
    }
    else if (token->type == RESERVED && token->value.res == Elif)
    {
        token_free(pop(lexer));
        else_clause->condition = grammar_compound_list_break(lexer);
        token = peek(lexer, 0);
        if (token->type != RESERVED || token->value.res != Then)
        {
            else_clause_node_free(else_clause);
            warnx("syntax error : expected token then");
            return NULL;
        }
        token_free(pop(lexer));
        else_clause->body = grammar_compound_list_break(lexer);
        else_clause->next = grammar_else_clause(lexer);
        return else_clause;
    }
    else
    {
        return else_clause;
        //else_clause_node_free(else_clause);
        //return NULL;
    }
}

struct rule_if_node *grammar_rule_if(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != If)
        return NULL;
    token_free(pop(lexer));

    struct rule_if_node *rule_if = xcalloc(1, sizeof(struct rule_if_node));

    rule_if->condition = grammar_compound_list_break(lexer);
    if (!rule_if->condition)
    {
        rule_if_node_free(rule_if);
        warnx("syntax error: expected condition");
        return NULL;
    }

    token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != Then)
    {
        rule_if_node_free(rule_if);
        warnx("syntax error: expected then");
        return NULL;
    }
    token_free(pop(lexer));

    rule_if->body = grammar_compound_list_break(lexer);
    if (!rule_if->body)
    {
        rule_if_node_free(rule_if);
        warnx("syntax error: expected body");
        return NULL;
    }

    rule_if->else_clause = grammar_else_clause(lexer);
    if (!rule_if->else_clause)
    {
        rule_if_node_free(rule_if);
        return NULL;
    }

    token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != Fi)
    {
        rule_if_node_free(rule_if);
        warnx("syntax error: expected fi");
        return NULL;
    }
    token_free(pop(lexer));

    return rule_if;
}
