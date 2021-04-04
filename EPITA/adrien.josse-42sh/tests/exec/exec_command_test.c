#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "utils/memory.h"

#include "parser/simple_command.h"

#include "exec/exec_command.h"
#include "exec/exec_simple_command.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    //cr_redirect_stderr();
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

Test(exec_simple_command, simple_command, .init=redirect_all_stdout)
{
    // GIVEN
    struct opt *opts = xcalloc(1, sizeof(struct opt));
    struct simple_command_node *simple_command =
        xcalloc(1, sizeof(struct simple_command_node));
    simple_command->elements = xcalloc(1, sizeof(struct element_node));
    simple_command->elements->type = String;
    simple_command->elements->content.word = strdup("echo");

    //WHEN
    int ret = exec_simple_command(simple_command, opts);

    //THEN
    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("\n", "");

    free(opts);
    free(simple_command->elements->content.word);
    free(simple_command->elements);
    free(simple_command);
}
