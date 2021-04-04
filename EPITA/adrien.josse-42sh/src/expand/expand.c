#include <string.h>
#include <stdlib.h>

#include "expand/expand.h"

#include "utils/memory.h"

#include "expand/expand_arithmetic.h"
#include "expand/expand_parameters.h"
#include "expand/expand_utils.h"
#include "expand/expand_tildes.h"
#include "expand/expand_command.h"
#include "expand/expand_path.h"
#include "expand/variables.h"

char *expand_vars(char *word, struct env *env, int tilde_exp)
{
    if (tilde_exp && strchr(word, '~'))
        word = expand_tildes(word, env);
    if (strchr(word, '$'))
        word = expand_parameters(word, env);
    if (strchr(word, '$') || strchr(word, '`'))
        word = expand_commands(word, env);
    if (strchr(word, '$'))
      word = expand_arithmetics(word, env);
    return word;
}

static int is_ifs(char test, char *ifs, int ifs_size)
{
    for (int i = 0; i < ifs_size; i++)
    {
        if (test == ifs[i])
            return 1;
    }
    return 0;
}

static struct splitted *field_split(char *word, struct env *env)
{
    struct splitted *splitted = xcalloc(1, sizeof(struct splitted));
    char *ifs;
    char *tmp_ifs = get_value(env, "IFS");
    if (*tmp_ifs)
        ifs = strdup(tmp_ifs);
    else
        ifs = strdup(" \t\n");
    int ifs_size = strlen(ifs);
    int word_idx = 0;
    while (word[word_idx])
    {
        while (word[word_idx] && is_ifs(word[word_idx], ifs, ifs_size))
            word_idx++;
        int len = 0;
        if (!word[word_idx])
            break;
        while (word[word_idx + len] && !is_ifs(word[word_idx + len], ifs,
                                               ifs_size))
            len++;
        splitted->split_words = xrealloc(splitted->split_words,
                                         sizeof(char *) * (splitted->size + 1));
        splitted->split_words[splitted->size++] = strndup(word + word_idx, len);
        word_idx += len;
    }
    free(ifs);
    return splitted;
}

static void splitted_list_free(struct splitted **splitted_list, int size)
{
    for(int i = 0; i < size; i++)
    {
        for (int j = 0; j < splitted_list[i]->size; j++)
        {
            free(splitted_list[i]->split_words[j]);
        }
        free(splitted_list[i]->split_words);
        free(splitted_list[i]);
    }
    free(splitted_list);
}

char *remove_quotes(char *word)
{
    int r_idx = 0;
    int w_idx = 0;
    char quote = 0;
    while (word[r_idx])
    {
        if (word[r_idx] != '\'' && word[r_idx] != '"' && word[r_idx] != '\\')
        {
            word[w_idx++] = word[r_idx];
        }
        else
        {
            if (!quote)
                quote = word[r_idx];
            else
            {
                if (quote == word[r_idx])
                    quote = 0;
                else
                    word[w_idx++] = word[r_idx];
            }
        }
        r_idx++;
    }
    word[w_idx] = '\0';
    word = xrealloc(word, w_idx + 1);
    return word;
}

char *expand_word(char *word, struct env *env)
{
    if (!word)
        return NULL;
    word = expand_vars(word, env, 1);
    if (strchr(word, '*') || strchr(word, '?')
            || strchr(word, '[') || strchr(word, ']'))
        word = expand_path(word);
    word = remove_quotes(word);
    if (!*word)
    {
        free(word);
        return NULL;
    }
    return word;
}

static struct splitted *handle_quotes(char *word, struct env *env)
{
    struct splitted *splitted = xcalloc(1, sizeof(struct splitted));
    splitted->size = 1;
    splitted->split_words = xcalloc(1, sizeof(char *));
    if (word[0] == '\'')
        splitted->split_words[0] = word;
    else
        splitted->split_words[0] = expand_vars(word, env, 1);
    return splitted;
}

char **expand_words(char **words, int *words_size, struct env *env)
{
    struct splitted **splitted_list = xcalloc(*words_size,
                                              sizeof(struct splitted));

    // Creates a struct "splitted" containing the new words corresponding to a
    // word after its expansion and field splitting for each word in the given
    // words array.
    for(int i = 0; i < *words_size; i++)
    {
        if (strchr(words[i], '\'') || strchr(words[i],'"'))
        {
            splitted_list[i] = handle_quotes(words[i], env);
            continue;
        }
        words[i] = expand_vars(words[i], env, 1);
        if (strchr(words[i], '*') || strchr(words[i], '?')
            || strchr(words[i], '[') || strchr(words[i], ']'))
            words[i] = expand_path(words[i]);
        splitted_list[i] = field_split(words[i], env);
        free(words[i]);
    }
    free(words);

    char **new_words = NULL;
    int old_words_size = *words_size;
    *words_size = 0;
    // Concatenates the sub_arrays in the structs "splitted"
    // to create a new_words array.
    for (int i = 0; i < old_words_size; i++)
    {
        for(int j = 0; j < splitted_list[i]->size; j++)
        {
            new_words = xrealloc(new_words, sizeof(char *) * (*words_size + 1));
            new_words[(*words_size)++] =
                strdup(splitted_list[i]->split_words[j]);
        }
    }

    splitted_list_free(splitted_list, old_words_size);

    if (!new_words)
        return NULL;

    // Expand pathnames & remove quotes on each word of the new words array.
    for (int i = 0; i < *words_size; i++)
    {

        new_words[i] = remove_quotes(new_words[i]);

        if (!*new_words[i])
        {
            free(new_words[i]);
            if (i + 1 < *words_size)
                new_words[i] = new_words[i + 1];
            (*words_size)--;
        }
    }

    new_words = xrealloc(new_words, *words_size * sizeof(char *));

    return new_words;
}
