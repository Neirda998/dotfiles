#include "parser/utils.h"

#include "lexer/token.h"

void skip_new_lines(struct lexer *lexer)
{
    struct token *token = peek(lexer, 0);
    while (token->type == NEW_LINE)
    {
        token_free(pop(lexer));
        token = peek(lexer, 0);
    }
}
