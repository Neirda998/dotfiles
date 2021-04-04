#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "built-in/built_in_alias.h"

#include "utils/memory.h"
#include "utils/xstring.h"

#include "input/readline.h"

#include "lexer/lexer.h"
#include "lexer/quote_len.h"
#include "lexer/split.h"


static void skip_blanks(char *str, int *idx)
{
    if(!str)
        return;
    while (isblank(str[*idx]) || str[*idx] == '#')
    {
        while (isblank(str[*idx]))
            (*idx)++;
        if (str[*idx] == '#')
        {
            while (str[*idx] != '\n' && str[*idx] != '\0')
                (*idx)++;
        }
    }
}

static int len_till_key(char *checked, char *keys[], int keys_len)
{
    if (!checked)
        return 0;
    for (int i = 0; i < keys_len; i++)
    {
        if (strncmp(checked, keys[i], strlen(keys[i])) == 0)
            return strlen(keys[i]);
    }
    return 0;
}

static int is_op_first(char *key)
{
    char *ops[15] =
    {
        ";;", "&&", "||", "(", ")", "|", "<<-",">>", "<<",  ">&", "<&", ">|",
        "<>", ">", "<"
    };
    return len_till_key(key, ops, 15);
}

int is_redir_first(char *key)
{
    char *ops[9] =
    {
        "<<-", ">>", "<<", ">&", "<&", ">|",
        "<>", ">", "<"
    };
    return len_till_key(key, ops, 9);
}

int is_single_split(struct lexer *lexer, int len)
{
    int idx = lexer->idx + len;
    if (lexer->str[idx] == '#' && idx > 0 && lexer->str[idx - 1] == '$')
        return 0;
    char c = lexer->str[idx];
    return c == '&' || c == '#' || c == ';' || c == '\n';
}

static int no_quotes_condition(struct lexer *lexer, int len)
{
    if (!lexer->str)
        return 0;
    return !lexer->str[lexer->idx + len]
        || isspace(lexer->str[lexer->idx + len])
        || is_op_first(lexer->str + lexer->idx + len)
        || is_single_split(lexer, len);
}

char *no_quotes(struct lexer *lexer, int alias)
{
    int len = 0;
    if (!lexer->str)
        exit(2);
    while (lexer->str[lexer->idx + len]
            && !isspace(lexer->str[lexer->idx + len])
            && !is_op_first(lexer->str + lexer->idx + len)
            && (!is_quote(lexer->str + lexer->idx + len)
                || is_quote(lexer->str + lexer->idx + len) > VAR_L)
            && !is_single_split(lexer, len))
    {
        if (!lexer->str)
            exit(2);
        if (lexer->str[lexer->idx + len] == '\\')
            len += 2;
        else
            len++;
    }
    char *word = strndup(lexer->str + lexer->idx, len);
    if (alias)
    {
        int search = alias_search(lexer->aliases, word);
        if (search != -1)
        {
            lexer->str = alias_expand(lexer->str, word,
                    lexer->aliases->data[search]->substitution,
                    lexer->idx);
            free(word);
            word = no_quotes(lexer, 0);
        }
        else
            lexer->idx += len;
    }
    else
        lexer->idx += len;
    return word;
}

char *word_subshell(struct lexer *lexer, enum quote_type quote)
{
    int len = quote_len(quote);
    char *word = NULL;
    quote += 3;
    while (1)
    {
        if (!lexer->str[lexer->idx + len]
                || lexer->str[lexer->idx + len] == '\n')
        {
            if (lexer->str)
            {
                word = xstrcat(word, strndup(lexer->str + lexer->idx, len));
                free(lexer->str);
            }
            lexer->str = get_next_line("42sh$ ", "> ", 1);
            len = 0;
            lexer->idx = 0;
        }
        enum quote_type type = is_quote(lexer->str + lexer->idx + len);\
        if (type >= DOUBLE && type <= COMMAND)
        {
            word = xstrcat(word, strndup(lexer->str + lexer->idx, len));
            lexer->idx += len;
            len = 0;
            word = xstrcat(word, word_ambi_quotes(lexer, type));
        }
        else if (type >= MATH_L && type <= VAR_L)
        {
            word = xstrcat(word, strndup(lexer->str + lexer->idx, len));
            lexer->idx += len;
            len = 0;
            word = xstrcat(word, word_subshell(lexer, type));
        }
        else if (type == quote)
        {
            len += quote_len(type);
            word = xstrcat(word, strndup(lexer->str + lexer->idx, len));
            lexer->idx += len;
            break;
        }
        else
        {
            if (!lexer->str)
            {
                warnx("syntax error: misisng `%s`",
                quote == SUB_R ? ")" : (quote == VAR_R ? "}" : "))"));
                exit(2);
            }
            if (lexer->str[lexer->idx + len] == '\\')
                len += 2;
            else
                len++;
        }
    }
    return word;
}

char *word_ambi_quotes(struct lexer *lexer, enum quote_type quote)
{
    int len = 1;
    char *word = NULL;
    while (1)
    {
        if (!lexer->str[lexer->idx + len]
                || lexer->str[lexer->idx + len] == '\n')
        {
            word = xstrcat(word, strndup(lexer->str + lexer->idx, len));
            free(lexer->str);
            lexer->str = get_next_line("42sh$ ", "> ", 1);
            len = 0;
            lexer->idx = 0;
        }
        enum quote_type type = is_quote(lexer->str + lexer->idx + len);
        if (type == MATH_L || type == SUB_L || type == VAR_L)
        {
            word = xstrcat(word, strndup(lexer->str + lexer->idx, len));
            lexer->idx += len;
            len = 0;
            word = xstrcat(word, word_subshell(lexer, type));
        }
        else if (type == quote)
        {
            len++;
            word = xstrcat(word, strndup(lexer->str + lexer->idx, len));
            lexer->idx += len;
            break;
        }
        else
        {
            if (!lexer->str)
            {
                warnx("syntax error: misisng `%s`",
                quote == COMMAND ? "`" : (quote == DOUBLE ? "\"" : "\'"));
                exit(2);
            }
            if (lexer->str[lexer->idx + len] == '\\')
                len += 2;
            else
                len++;
        }
    }
    return word;
}

char *next_word(struct lexer *lexer, int alias)
{
    char *word = NULL;
    skip_blanks(lexer->str, &lexer->idx);
    if (is_op_first(lexer->str + lexer->idx))
    {
        int len = is_op_first(lexer->str + lexer->idx);
        word = strndup(lexer->str + lexer->idx, len);
        lexer->idx += len;
        return word;
    }
    else if (is_single_split(lexer, 0)
            && *(lexer->str + lexer->idx) != '#')
    {
        word = strndup(lexer->str + lexer->idx, 1);
        lexer->idx++;
        return word;
    }
    while (1)
    {
        word = xstrcat(word, no_quotes(lexer, alias));
        enum quote_type quote = is_quote(lexer->str + lexer->idx);
        if (no_quotes_condition(lexer, 0))
            return word;
        if (quote >= MATH_L && quote <= VAR_L)
            word = xstrcat(word, word_subshell(lexer, quote));
        else if (quote >= DOUBLE && quote <= COMMAND)
            word = xstrcat(word, word_ambi_quotes(lexer, quote));
    }
    return word;
}
