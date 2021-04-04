#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <stdio.h>
#include <readline/readline.h>

#include "utils/memory.h"

#include "input/input.h"
#include "input/readline.h"

/*
static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}*/

Test(get_next_line, simple_line)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "echo toto");
    // WHEN
    char *line1 = get_next_line("420sh ", "> ", 0);
    // THEN
    cr_assert_str_eq(line1, "echo toto");
    free(line1);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(get_next_line, double_line)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "420sh\nBlaze it!");
    // WHEN
    char *line1 = get_next_line("420sh ", "> ", 0);
    char *line2 = get_next_line("420sh ", "> ", 0);
    // THEN
    cr_assert_str_eq(line1, "420sh\n");
    cr_assert_str_eq(line2, "Blaze it!");
    free(line1);
    free(line2);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(get_next_line, empty_line)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "");
    // WHEN
    char *line1 = get_next_line("420sh ", "> ", 0);
    // THEN
    cr_assert_str_eq(line1, "");
    free(line1);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
