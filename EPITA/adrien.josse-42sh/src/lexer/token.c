#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/memory.h"
#include "utils/xstring.h"

#include "lexer/token.h"

/**
** Initialize a token as a WORD token.
** @param str Value of the token.
** @return Return a valid END_OF_FILE token.
*/
static struct token *token_init(char *str)
{
    struct token *new = xmalloc(sizeof(struct token));

    new->value.str = str;
    new->type = WORD;
    return new;
}

static int get_number_value(char *str)
{
    if (!is_number(str))
        return -1;
    if (strlen(str) >= 11)
        return -1;
    int num = atoi(str);
    if (num < 0)
        return -1;
    return num;
}

int get_reserved_word(const char *str)
{
    char *words[] =
    {
        "if", "then", "else", "elif", "fi", "do", "done", "case", "esac",
        "while", "until", "for", "{", "}", "!", "in"
    };

    for (size_t i = 0; i < sizeof(words) / sizeof(char*); ++i)
    {
        if (strcmp(words[i], str) == 0)
            return i;
    }
    return -1;
}

int get_operator_value(const char *str)
{
    char *words[] =
    {
        ";;", "&&", "||", "(", ")", "|", "<<-",">>", "<<",  ">&", "<&", ">|",
        "<>", ">", "<"
    };

    for (size_t i = 0; i < sizeof(words) / sizeof(char*); ++i)
    {
        if (strcmp(words[i], str) == 0)
            return i;
    }
    return -1;
}

static void set_to_type(struct token *token, int *found, enum token_type type)
{
    token->type = type;
    token->value.str = NULL;
    *found = 1;
}

static void set_to_OPERATOR(struct token *token, int *found, int value)
{
    token->type = OPERATOR;
    token->value.op = value;
    *found = 1;
}

static void set_to_RESERVED(struct token *token, int *found, int value)
{
    token->type = RESERVED;
    token->value.res = value;
    *found = 1;
}

struct token *token_create(char *str, int is_cmd)
{
    struct token *token = token_init(str);
    int found = 0;
    int test = strcmp("", str);
    if(!test)
        set_to_type(token, &found, END_OF_FILE);
    test = strcmp("\n", str);
    if(!test)
        set_to_type(token, &found, NEW_LINE);
    test = strcmp(";", str);
    if(!test)
        set_to_type(token, &found, SEMI);
    test = strcmp("&", str);
    if(!test)
        set_to_type(token, &found, AND);
    test = get_operator_value(str);
    if (test != -1)
        set_to_OPERATOR(token, &found, test);
    test = is_number(str);
    if (test != -1 && is_cmd == 2)
    {
        if (get_number_value(str) >= 0)
            set_to_type(token, &found, IO_NUMBER);
        else
            set_to_type(token, &found, WORD);
        token->value.str = str;
        return token;
    }
    if (is_cmd == 1)
    {
        if (found)
            free(str);
        return token;
    }
    test = get_reserved_word(str);
    if (test != -1 && !is_cmd)
        set_to_RESERVED(token, &found, test);
    if (found)
        free(str);
    else
        token->type = is_number(str) ? IO_NUMBER : WORD;
    return token;
}

void token_free(struct token *token)
{
    if (token->type == WORD || token->type == IO_NUMBER)
        free(token->value.str);
    free(token);
}
