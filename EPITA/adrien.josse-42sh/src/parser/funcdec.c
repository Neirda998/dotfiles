#include <ctype.h>
#include <err.h>
#include <string.h>

#include "utils/memory.h"

#include "lexer/token.h"

#include "parser/funcdec.h"
#include "parser/utils.h"

#include "free/funcdec_free.h"

struct funcdec_node *grammar_funcdec(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    struct funcdec_node *funcdec = NULL;

    if (token->type != WORD)
        return NULL;

    if (strcmp(token->value.str, "function") == 0)
    {
        token_free(pop(lexer));
        token = peek(lexer, 0);
        if (token->type != WORD)
        {
            warnx("syntax error: invalid function name");
            return NULL;
        }
    }
    else
    {
        int tmp_idx = lexer->idx;
        while (isblank(lexer->str[tmp_idx]))
            tmp_idx++;
        if (lexer->str[tmp_idx] != '(')
            return NULL;
    }

    funcdec = xcalloc(1, sizeof(struct funcdec_node));
    funcdec->name = strdup(token->value.str);

    token_free(pop(lexer));

    token = peek(lexer, 0);
    if (token->type != OPERATOR || token->value.op != L_PARENTHESIS)
    {
        funcdec_node_free(funcdec);
        // warnx("syntax error: expected '('");
        return NULL;
    }
    token_free(pop(lexer));

    token = peek(lexer, 0);
    if (token->type != OPERATOR || token->value.op != R_PARENTHESIS)
    {
        funcdec_node_free(funcdec);
        warnx("syntax error: expected ')'");
        return NULL;
    }
    token_free(pop(lexer));

    skip_new_lines(lexer);

    funcdec->body = grammar_shell_command(lexer);
    if (!funcdec->body)
    {
        funcdec_node_free(funcdec);
        warnx("syntax error: expected body");
        return NULL;
    }
    return funcdec;
}
