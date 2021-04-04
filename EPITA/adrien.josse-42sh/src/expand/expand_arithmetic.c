#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "expand/expand_arithmetic.h"

#include "expand/expand_utils.h"

#include "expand/expand_arithmetic_exec.h"
#include "expand/expand_arithmetic_free.h"
#include "expand/expand_arithmetic_free_2.h"
#include "expand/expand_arithmetic_lexer.h"
#include "expand/expand_arithmetic_parser.h"

static long long arithmetic_evaluation(char *str, struct env *env)
{
    struct a_lexer *a_lexer = set_a_lexer(str);
    struct expr *expr = parse_expression(a_lexer);
    if (!expr)
    {
        unset_a_lexer(a_lexer);
        return 0;
    }
    long long eval = expr_eval(expr, env);
    free_or(expr->or);
    unset_a_lexer(a_lexer);
    free(expr);

    return eval;
}

static char *expand_arithmetic(char *word, struct env *env)
{
    long long ret = arithmetic_evaluation(word, env);
    char char_ret[500];
    sprintf(char_ret, "%lld", ret);
    return strdup(char_ret);
}

char *expand_arithmetics(char *word, struct env *env)
{
    char quote = 0;
    if (!word)
        return NULL;
    int idx = 0;
    while (word[idx])
    {
        if (quote != '\'' && word[idx] == '$' && word[idx + 1] == '('
            && word[idx + 2] == '(')
        {
            int len = 0;
            char *full_expansion;
            char *to_expand;
            while (word[idx + len + 3] != ')' || word[idx + len + 4] != ')')
                len++;
            full_expansion = strndup(word + idx, len + 5);
            to_expand = strndup(word + idx + 3, len);
            char *expand_val = expand_arithmetic(to_expand, env);
            char *res = expand_in_str(word, full_expansion, expand_val);
            free(to_expand);
            idx += strlen(expand_val);
            free(full_expansion);
            free(expand_val);
            word = res;
        }
        else
        {
            if (word[idx] == '\'' || word[idx] == '"')
            {
                if (!quote)
                    quote = word[idx];
                else if (quote == word[idx])
                    quote = 0;
            }
            idx++;
        }
    }
    return word;
}
