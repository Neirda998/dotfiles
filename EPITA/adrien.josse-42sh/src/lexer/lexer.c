#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#include "utils/memory.h"
#include "utils/xstring.h"

#include "input/readline.h"

#include "lexer/lexer.h"
#include "lexer/split.h"

static void first_skip_blanks(char *str, int *idx)
{
    if (!str)
        return;
    while (isblank(str[*idx]))
        *idx = *idx + 1;
}

struct lexer *set_lexer(struct aliases *aliases)
{
    struct lexer *lexer = xcalloc(1, sizeof(struct lexer));
    // TODO
    // update prompt to get actual PS1 & PS2
    lexer->str = get_next_line("42sh$ ", "> ", 0);
    lexer->aliases = aliases;
    return lexer;
}

static char *pop_heredoc(struct lexer *lexer, char *key)
{
    char *word = NULL;
    int len = 0;
    int key_len = strlen(key);
    while (1)
    {
        if (!lexer->str || !lexer->str[lexer->idx + len])
        {
            word = xstrcat(word, strndup(lexer->str + lexer->idx, len));
            free(lexer->str);
            lexer->str = get_next_line("42sh$ ", "> ", 1);
            lexer->idx = 0;
            len = 0;
        }
        else if (strncmp(lexer->str, key, key_len) == 0
                 && (lexer->str[key_len] == '\n'
                 || lexer->str[key_len] == '\0'))
        {
            lexer->idx += len + key_len;
            return word;
        }
        else
            len++;
    }
    return NULL;
}

static void handle_redirect(struct lexer *lexer)
{
    int i = 0;
    while (i < lexer->here_idx)
    {
        char *key = strdup(*lexer->heredocs[i]);
        free(*lexer->heredocs[i]);
        *lexer->heredocs[i] = pop_heredoc(lexer, key);
        free(key);
        i++;
    }

    free(lexer->heredocs);
    lexer->here_idx = 0;
    lexer->heredocs = NULL;
}

struct token *peek(struct lexer *lexer, int is_cmd)
{
    struct token *token = lexer->next_token;
    if (!token)
    {
        first_skip_blanks(lexer->str, &lexer->idx);
        if (!lexer->str || !lexer->str[lexer->idx])
        {
            if (lexer->heredocs)
            {
                handle_redirect(lexer);
            }
            else
            {
                free(lexer->str);
                lexer->str = get_next_line("42sh$ ", "> ", 1);
                lexer->idx = 0;
            }
            if (lexer->heredocs)
                handle_redirect(lexer);
        }
        if (!lexer->str)
        {
            token = token_create(strdup(""), 0);
            lexer->next_token = token;
            return token;
        }
        char *word = next_word(lexer, !is_cmd);
        if (is_redir_first(lexer->str + lexer->idx))
            token = token_create(word, 2);
        else
            token = token_create(word, is_cmd);
        lexer->next_token = token;
    }
    return token;
}

struct token *pop(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    lexer->next_token = NULL;
    return token;
}

struct token *pop_command(struct lexer *lexer)
{
    struct token *token = peek(lexer, 1);
    lexer->next_token = NULL;
    return token;
}
/*
struct token *pop_command(struct lexer *lexer)
{
    if (!lexer->str[lexer->idx])
    {
        free(lexer->str);
        lexer->str = get_next_line("420sh$ ", "> ", 1);
        lexer->idx = 0;
    }
    char *cmd = next_command(lexer->str, &lexer->idx);
    struct token *token = token_create(cmd);
    return token;
}
*/
void unset_lexer(struct lexer *lexer)
{
    if (lexer->next_token)
        token_free(lexer->next_token);
    //for (int i = 0; i < lexer->here_idx; i++)
    //    free(*lexer->heredocs[i]);
    free(lexer->heredocs);
    free(lexer->str);
    free(lexer);
}
