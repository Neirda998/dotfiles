#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "parser/case.h"

#include "utils/memory.h"

#include "parser/utils.h"

#include "free/case_free.h"

struct rule_case_node *grammar_rule_case(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);

    if (token->type != RESERVED || token->value.res != Case)
        return NULL;
    token_free(pop(lexer));

    struct rule_case_node *rule_case = xcalloc(1, sizeof(*rule_case));

    token = peek(lexer, 1);
    if (token->type != WORD)
    {
        rule_case_node_free(rule_case);
        warnx("syntax error: expected expression after case");
        return NULL;
    }
    rule_case->expression = strdup(token->value.str);
    token_free(pop_command(lexer));

    skip_new_lines(lexer);

    token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != In)
    {
        rule_case_node_free(rule_case);
        warnx("syntax error: expected in");
        return NULL;
    }
    token_free(pop(lexer));

    skip_new_lines(lexer);

    rule_case->case_clause = grammar_case_clause(lexer);

    token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != Esac)
    {
        rule_case_node_free(rule_case);
        warnx("syntax error: expected esac");
        return NULL;
    }
    token_free(pop(lexer));

    return rule_case;
}

struct case_clause_node *grammar_case_clause(struct lexer *lexer)
{
    struct case_clause_node *case_clause = xcalloc(1, sizeof(*case_clause));

    case_clause->case_item = grammar_case_item(lexer);
    if (!case_clause->case_item)
    {
        case_clause_node_free(case_clause);
        return NULL;
    }

    struct token *token = peek(lexer, 0);
    struct case_item_node *cur = case_clause->case_item;
    while (token->type == OPERATOR && token->value.op == DSEMI)
    {
        token_free(pop(lexer));
        skip_new_lines(lexer);
        cur->next = grammar_case_item(lexer);
        if (!cur->next)
            break;
        cur = cur->next;
        token = peek(lexer, 0);
    }
    skip_new_lines(lexer);
    return case_clause;
}

/**
** Fills array of patterns in CASE ITEM NODE struct.
** @param the case item struct.
*/
static struct case_item_node *set_case_patterns(struct lexer *lexer,
                                       struct case_item_node *case_item)
{
    int idx = 0;
    struct token *token = peek(lexer, 0);
    if (token->type != WORD)
    {
        case_item_node_free(case_item);
        warnx("syntax error: unexpected token in patterns");
        return NULL;
    }
    case_item->patterns = xmalloc(sizeof(char *));

    case_item->patterns[idx++] = strdup(token->value.str);
    token_free(pop(lexer));

    token = peek(lexer, 0);
    while (token->type == OPERATOR && token->value.op == PIPE)
    {
        token_free(pop(lexer));
        token = peek(lexer, 1);
        if (token->type != WORD)
        {
            case_item_node_free(case_item);
            warnx("syntax error: unexpected token in patterns");
            return NULL;
        }

        case_item->patterns = xrealloc(case_item->patterns,
                                       (idx + 1) * sizeof(char *));
        case_item->patterns[idx++] = strdup(token->value.str);
        token_free(pop_command(lexer));
        token = peek(lexer, 0);
    }
    case_item->size = idx;
    return case_item;
}

struct case_item_node *grammar_case_item(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    if (token->type == OPERATOR && token->value.op == L_PARENTHESIS)
    {
        token_free(pop(lexer));
        token = peek(lexer, 1);
        if (token->type != WORD)
        {
            warnx("syntax error: unexpected token in case_item");
            return NULL;
        }
    }
    else
    {
        token = peek(lexer, 1);
        if (token->type != WORD)
            return NULL;
    }

    struct case_item_node *case_item = xcalloc(1, sizeof(*case_item));
    if (!case_item)
        return NULL;
    set_case_patterns(lexer, case_item);

    token = peek(lexer, 0);
    if (token->type != OPERATOR || token->value.op != R_PARENTHESIS)
    {
        case_item_node_free(case_item);
        warnx("syntax error: expected ')'");
        return NULL;
    }
    token_free(pop(lexer));

    skip_new_lines(lexer);
    token = peek(lexer, 0);

    case_item->statement = grammar_compound_list(lexer);

    return case_item;
}
