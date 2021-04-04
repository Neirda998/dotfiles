#include <criterion/criterion.h>

#include <stdlib.h>

#include "utils/memory.h"

#include "expand/expand_tildes.h"
#include "expand/variables.h"

Test(expand_tildes, simple_tilde_expand)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();
    char *name = strdup("HOME");
    char *value = strdup("/home/epita");
    char *word = strdup("~");
    env = set_value(env, name, value);

    // WHEN
    char *res = expand_tildes(word, env);

    // THEN
    cr_expect_str_eq(res, "/home/epita");

    env_free(env);
    free(res);
}

Test(expand_tildes, no_tilde)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();
    char *word = strdup("abc");

    // WHEN
    char *res = expand_tildes(word, env);

    // THEN
    cr_expect_str_eq(res, "abc");

    env_free(env);
    free(res);
}

Test(expand_tildes, username_tilde)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();
    char *word = strdup("~root");

    // WHEN
    char *res = expand_tildes(word, env);

    // THEN
    cr_expect_str_eq(res, "/root");

    env_free(env);
    free(res);
}

Test(expand_tildes, invalid_username_tilde)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();
    char *word = strdup("~blublublufu");

    // WHEN
    char *res = expand_tildes(word, env);

    // THEN
    cr_expect_str_eq(res, "~blublublufu");

    env_free(env);
    free(res);
}
