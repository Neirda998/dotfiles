#include <string.h>
#include <stdlib.h>

#include "expand/expand_parameters.h"
#include "expand/variables.h"
#include "expand/expand_utils.h"

static int is_special_char(char c)
{
    return c == '@' || c == '*' || c == '?' || c == '$'
        || (c >= '0' && c <= '9') || c == '#';
}

static int is_valid_var_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9') || c == '_';
}


char *expand_parameters(char *word, struct env *env)
{
    int is_subshell = 0;
    char quote = 0;
    if (!word)
        return word;

    int idx = 0;
    while (word[idx])
    {
        if (quote != '\'' && !is_subshell && word[idx] == '$' && word[idx + 1]
            && word[idx + 1] != '(' && (idx - 1 < 0 || word[idx - 1] != '\\'))
        {
            int len = 0;
            int is_braces = word[idx + 1] == '{';
            char *full_name;
            char *var_name = NULL;
            if (is_braces)
            {
                while (word[idx + len + 2] != '}')
                    len++;

                full_name = strndup(word + idx, len + 3);
                var_name = strndup(word + idx + 2, len);
            }
            else
            {
                if (is_special_char(word[idx + len + 1]))
                    len = 1;
                else
                {
                    while (is_valid_var_char(word[idx + len + 1]))
                        len++;
                }

                full_name = strndup(word + idx, len + 1);
                if (len)
                    var_name = strndup(word + idx + 1, len);
            }
            char *var_value = "";
            if (var_name)
                var_value = get_value(env, var_name);
            char *res = expand_in_str(word, full_name, var_value);
            free(var_name);
            idx += strlen(var_value);
            free(full_name);
            word = res;
        }
        else
        {
            if ((word[idx] == '$' && word[idx + 1] == '('
                    && word[idx + 2] != '(')
                        || word[idx] == '`')
                is_subshell = 1;
            else if (is_subshell && (word[idx] == ')' || word[idx] == '`'))
                is_subshell = 0;
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
