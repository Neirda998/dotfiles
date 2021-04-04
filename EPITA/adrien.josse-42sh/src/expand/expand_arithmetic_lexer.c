#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expand/expand_arithmetic_lexer.h"

#include "utils/memory.h"

struct a_lexer *set_a_lexer(char *str)
{
    struct a_lexer *a_lexer = xcalloc(1, sizeof(struct a_lexer));

    a_lexer->str = strdup(str);
    return a_lexer;
}

static int is_in(char *str, char *keys[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (strcmp(str, keys[i]) == 0)
            return i + 1;
    }
    return 0;
}

static int len_reserved_first(char *str)
{
    char *reserved[] = {
        "+", "-", "/", "**", "*",
        "&&", "&", "||", "|", "^", "~", "!",
        "(", ")"
    };
    int len = sizeof(reserved) / sizeof(char *);
    for (int i = 0; i < len; i++)
    {
        int ln = strlen(reserved[i]);
        if (strncmp(str, reserved[i], ln) == 0)
            return ln;
    }
    return 0;
}

struct a_token *a_token_create(char *str, int unary)
{
    struct a_token *token = xcalloc(1, sizeof(*token));

    if (strcmp("", str) == 0)
    {
        token->type = END;
        return token;
    }

    if (strcmp(str, "(") == 0)
    {
        token->type = L_PARENTHESIS;
        return token;
    }
    if (strcmp(str, ")") == 0)
    {
        token->type = R_PARENTHESIS;
        return token;
    }

    char *u_ops[] = {
        "+", "-", "!", "~"
    };
    char *b_ops[] = {
        "+", "-", "**", "*", "/", "&&", "||", "&", "|", "^"
    };

    if (unary)
    {
        token->u_op = is_in(str, u_ops, 4);
        if (token->u_op)
        {
            token->type = U_OP;
            return token;
        }
    }
    token->b_op = is_in(str, b_ops, 10);
    if (token->b_op)
    {
        token->type = B_OP;
        return token;
    }

    token->value = strdup(str);
    return token;
}

struct a_token *a_peek(struct a_lexer *a_lexer, int unary)
{
    struct a_token *token = a_lexer->next_token;
    if (token)
        return token;

    char *word = NULL;
    int len = 0;

    while (isspace(a_lexer->str[a_lexer->idx]))
        a_lexer->idx++;

    if (!a_lexer->str[a_lexer->idx])
    {
        a_lexer->next_token = a_token_create("", 0);
        return a_lexer->next_token;
    }

    len = len_reserved_first(a_lexer->str + a_lexer->idx);
    if (len)
    {
        word = strndup(a_lexer->str + a_lexer->idx, len);
        a_lexer->idx += len;
        a_lexer->next_token = a_token_create(word, unary);
        free(word);
    }
    else
    {
        while (a_lexer->str[a_lexer->idx + len]
                && !isspace(a_lexer->str[a_lexer->idx + len])
                && !len_reserved_first(a_lexer->str + a_lexer->idx + len))
            len++;
        word = strndup(a_lexer->str + a_lexer->idx, len);
        a_lexer->idx += len;
        a_lexer->next_token = a_token_create(word, unary);
        free(word);
    }
    return a_lexer->next_token;
}

struct a_token *a_pop(struct a_lexer *a_lexer, int unary)
{
    struct a_token *token = a_peek(a_lexer, unary);
    a_lexer->next_token = NULL;
    return token;
}

void a_token_free(struct a_token *token)
{
    free(token->value);
    free(token);
}

void unset_a_lexer(struct a_lexer *a_lexer)
{
    if (a_lexer->next_token)
        a_token_free(a_lexer->next_token);
    free(a_lexer->str);
    free(a_lexer);
}
