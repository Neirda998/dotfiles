#include <ctype.h>
#include <err.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "parser/redirection.h"

#include "utils/memory.h"
#include "utils/xstring.h"

#include "lexer/lexer.h"
#include "lexer/token.h"

#include "expand/expand.h"

#include "free/redirection_free.h"

static void push_heredoc(struct lexer *lexer, struct redirection_node *redir)
{
    lexer->heredocs = xrealloc(lexer->heredocs, sizeof(char *)
                             * (lexer->here_idx + 1));
    lexer->heredocs[lexer->here_idx] = &redir->redirect_out;
    for (size_t i = 0; redir->redirect_out[i]; i++)
    {
        if (redir->redirect_out[i] == '\''
            || redir->redirect_out[i] == '"'
            || redir->redirect_out[i] == '\\')
        {
            redir->expand = 0;
            break;
        }
    }
    redir->redirect_out = remove_quotes(redir->redirect_out);
    lexer->here_idx++;
}

struct redirection_node *grammar_redirection(struct lexer *lexer)
{
    struct redirection_node *node = xcalloc(1,
                                        sizeof(struct redirection_node));
    node->expand = 1;
    struct token *token = peek(lexer, 0);
    if (token->type == IO_NUMBER)
    {
        node->ionumber = atoi(token->value.str);
        token_free(pop(lexer));
    }
    else
        node->ionumber = -1;

    token = peek(lexer, 0);
    if (token->type != OPERATOR || token->value.op <= PIPE)
    {
        redirection_node_free(node);
        return NULL;
    }
    node->op = token->value.op;
    token_free(pop(lexer));

    token = peek(lexer, 0);
    if (token->type <= RESERVED)
    {
        redirection_node_free(node);
        warnx("syntax error: unexpected token near redirection");
        return NULL;
    }
    node->redirect_out = strdup(token->value.str);
    token_free(pop(lexer));

    if (node->op == DLESS || node->op == DLESSDASH)
        push_heredoc(lexer, node);

    return node;
}
