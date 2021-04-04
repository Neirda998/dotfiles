#include <criterion/criterion.h>

#include <string.h>

#include "utils/memory.h"

#include "input/env.h"

#include "expand/variables.h"

Test(set_value, simple_value)
{
    // WHEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();

    char *name = strdup("test_name");
    char *value = strdup("value_name");
    // WHEN
    env = set_value(env, name, value);

    // THEN
    cr_expect_not_null(env);
    cr_expect_not_null(env->vars);
    cr_expect_not_null(env->vars->head);
    cr_expect_str_eq(env->vars->head->name, "test_name");
    cr_expect_str_eq(env->vars->head->value, "value_name");
    cr_expect_null(env->vars->head->next);

    env_free(env);
}

Test(set_value, multiple_word_value)
{
    // WHEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();

    char *name = strdup("test_name");
    char *value = strdup("value name");
    // WHEN
    env = set_value(env, name, value);

    // THEN
    cr_expect_not_null(env);
    cr_expect_not_null(env->vars);
    cr_expect_not_null(env->vars->head);
    cr_expect_str_eq(env->vars->head->name, "test_name");
    cr_expect_str_eq(env->vars->head->value, "value name");
    cr_expect_null(env->vars->head->next);

    env_free(env);
}

Test(set_value, already_set_var)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();

    char *name = strdup("test_name");
    char *value = strdup("value_name");
    env = set_value(env, name, value);
    char *new_name = strdup("test_name");
    char *new_value = strdup("new value");

    // WHEN
    env = set_value(env, new_name, new_value);

    // THEN
    cr_expect_not_null(env);
    cr_expect_not_null(env->vars);
    cr_expect_not_null(env->vars->head);
    cr_expect_str_eq(env->vars->head->name, "test_name");
    cr_expect_str_eq(env->vars->head->value, "new value");
    cr_expect_null(env->vars->head->next);

    env_free(env);
}
