#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "utils/memory.h"

#include "input/env.h"

#include "parser/simple_command.h"

#include "expand/expand.h"
#include "expand/variables.h"

#include "free/simple_command_free.h"

#include "exec/exec_command.h"
#include "exec/exec_simple_command.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    //cr_redirect_stderr();
}

Test(exec_prefix, add_basic_var)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();

    struct prefix_node *prefix =
        xcalloc(1, sizeof(struct prefix_node));
    prefix->type = String;
    prefix->content.word = strdup("420=Blaze_it!");

    // WHEN
    int ret = exec_prefix(prefix, env);

    // THEN
    cr_expect_eq(ret, 0);
    cr_expect_eq(env->vars->len, 1);
    cr_assert_not_null(env->vars->head);
    cr_expect_str_eq(env->vars->head->name, "420");
    cr_expect_str_eq(env->vars->head->value, "Blaze_it!");
    cr_assert_null(env->vars->head->next);

    env_free(env);
    prefix_node_free(prefix);
}

Test(exec_prefix, add_empty_var)
{
    // GIVEN
    struct env *env = xcalloc(1, sizeof(struct env));
    env->vars = init_vars();

    struct prefix_node *prefix =
        xcalloc(1, sizeof(struct prefix_node));
    prefix->type = String;
    prefix->content.word = strdup("420=");

    // WHEN
    int ret = exec_prefix(prefix, env);

    // THEN
    cr_expect_eq(ret, 0);
    cr_expect_eq(env->vars->len, 1);
    cr_assert_not_null(env->vars->head);
    cr_expect_str_eq(env->vars->head->name, "420");
    cr_expect_str_eq(env->vars->head->value, "");
    cr_assert_null(env->vars->head->next);

    env_free(env);
    prefix_node_free(prefix);
}

Test(execute, simple_command, .init=redirect_all_stdout)
{
    // GIVEN
    char **argv = xcalloc(3, sizeof(char *));
    argv[0] = strdup("echo");
    argv[1] = strdup("then");
    argv[2] = NULL;

    // WHEN
    int ret = execute(argv);

    // THEN
    cr_expect_eq(ret, 0);
    cr_assert_stdout_eq_str("then\n", "");
}
