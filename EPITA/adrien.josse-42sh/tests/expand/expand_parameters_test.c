#include <criterion/criterion.h>

#include <string.h>
#include <stdlib.h>

#include "utils/memory.h"

#include "expand/expand_parameters.h"
#include "expand/variables.h"

Test(expand_parameters, one_existing_param)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();
    char *name = strdup("name");
    char *value = strdup("value");
    char *word = strdup("$name");
    env = set_value(env, name, value);

    // WHEN
    char *res = expand_parameters(word, env);

    // THEN
    cr_expect_str_eq(res, "value");

    env_free(env);
    free(res);
}

Test(expand_parameters, one_absent_param)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();
    char *word = strdup("$name");

    // WHEN
    char *res = expand_parameters(word, env);

    // THEN
    cr_expect_str_eq(res, "");

    env_free(env);
    free(res);
}

Test(expand_parameters, multi_existing_param)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();
    char *name = strdup("multi");
    char *value = strdup("dorifutingu");
    char *name2 = strdup("name");
    char *value2 = strdup("myo_dead");

    env = set_value(env, name, value);
    env = set_value(env, name2, value2);

    char *word = strdup("$multi$name");
    // WHEN
    char *res = expand_parameters(word, env);

    // THEN
    cr_expect_str_eq(res, "dorifutingumyo_dead");

    env_free(env);
    free(res);
}
