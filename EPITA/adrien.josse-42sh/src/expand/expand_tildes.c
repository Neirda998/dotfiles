#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pwd.h>

#include "expand/variables.h"
#include "expand/expand_utils.h"

static char *expand_tilde(char *word, struct env *env)
{
    char *home;
    if (strcmp("~", word) == 0)
    {
        home = strdup(get_value(env, "HOME"));
        return home;
    }
    if (strcmp("~+", word) == 0)
    {
        home = strdup(get_value(env, "PWD"));
        return home;
    }
    if (strcmp("~-", word) == 0)
    {
        home = strdup(get_value(env, "OLDPWD"));
        return home;
    }
    struct passwd *pwd = getpwnam(word + 1);
    if (!pwd)
        return strdup(word);
    home = strdup(pwd->pw_dir);
    return home;
}

char *expand_tildes(char *word, struct env *env)
{
    if (!word || *word != '~')
        return word;

    int len = 0;
    while (word[len] && !isspace(word[len]) && word[len] != '/'
          && word[len] != ':')
        len++;

    char *tilde_word = strndup(word, len);
    char *expanded = expand_tilde(tilde_word, env);
    char *res = expand_in_str(word, tilde_word, expanded);

    free(tilde_word);
    free(expanded);
    return res;
}
