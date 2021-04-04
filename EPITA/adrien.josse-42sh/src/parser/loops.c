#include <err.h>
#include <stddef.h>
#include <string.h>

#include "parser/loops.h"

#include "utils/memory.h"

#include "parser/utils.h"

#include "free/loops_free.h"

struct do_group_node *grammar_do_group(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != Do)
        return NULL;
    token_free(pop(lexer));

    struct do_group_node *do_group = xcalloc(1, sizeof(struct do_group_node));

    do_group->body = grammar_compound_list_break(lexer);
    if (!do_group->body)
    {
        do_group_node_free(do_group);
        warnx("syntax error: expected body");
        return NULL;
    }

    token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != Done)
    {
        do_group_node_free(do_group);
        warnx("syntax error: expected done");
        return NULL;
    }
    token_free(pop(lexer));

    return do_group;
}

struct rule_while_node *grammar_rule_while(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != While)
        return NULL;
    token_free(pop(lexer));

    struct rule_while_node *rule_while = xcalloc(1,
                                            sizeof(struct rule_while_node));

    rule_while->condition = grammar_compound_list_break(lexer);
    if (!rule_while->condition)
    {
        rule_while_node_free(rule_while);
        warnx("syntax error: expected condition");
        return NULL;
    }

    rule_while->body = grammar_do_group(lexer);
    if (!rule_while->body)
    {
        rule_while_node_free(rule_while);
        warnx("syntax error: expected body");
        return NULL;
    }

    return rule_while;
}

struct rule_until_node *grammar_rule_until(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != Until)
        return NULL;
    token_free(pop(lexer));

    struct rule_until_node *rule_until = xcalloc(1,
                                            sizeof(struct rule_until_node));

    rule_until->condition = grammar_compound_list_break(lexer);
    if (!rule_until->condition)
    {
        rule_until_node_free(rule_until);
        warnx("syntax error: expected condition");
        return NULL;
    }

    rule_until->body = grammar_do_group(lexer);
    if (!rule_until->body)
    {
        rule_until_node_free(rule_until);
        warnx("syntax error: expected body");
        return NULL;
    }

    return rule_until;
}

struct rule_for_node *grammar_rule_for(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != For)
        return NULL;
    token_free(pop(lexer));

    token = peek(lexer, 1);
    if (token->type != WORD)
    {
        warnx("syntax error: expected iterator");
        return NULL;
    }
    if (strchr(token->value.str, '$'))
    {
        warnx("`%s': not a valid identifier", token->value.str);
        return NULL;
    }

    struct rule_for_node *rule_for = xcalloc(1, sizeof(struct rule_for_node));
    rule_for->iterator = strdup(token->value.str);
    rule_for->size = 0;
    token_free(pop_command(lexer));

    token = peek(lexer, 0);
    if (token->type == SEMI)
        token_free(pop(lexer));
    else
    {
        skip_new_lines(lexer);
        if (token->type != RESERVED || token->value.res != In)
        {
            rule_for_node_free(rule_for);
            warnx("syntax error: expected token in");
            return NULL;
        }
        token_free(pop(lexer));

        token = peek(lexer, 1);
        int idx = 0;
        while (token->type == WORD)
        {
            rule_for->iterated = xrealloc(rule_for->iterated,
                                        sizeof(char *) * (idx + 1));
            rule_for->iterated[idx++] = strdup(token->value.str);
            rule_for->size++;
            token_free(pop_command(lexer));
            token = peek(lexer, 1);
        }

        if (token->type != SEMI && token->type != NEW_LINE)
        {
            rule_for_node_free(rule_for);
            warnx("syntax error: unexpected token");
            return NULL;
        }
        token_free(pop_command(lexer));
        token = peek(lexer, 0);
    }

    skip_new_lines(lexer);
    rule_for->body = grammar_do_group(lexer);
    if (!rule_for->body)
    {
        rule_for_node_free(rule_for);
        warnx("syntax error: expected body");
        return NULL;
    }

    return rule_for;
}
