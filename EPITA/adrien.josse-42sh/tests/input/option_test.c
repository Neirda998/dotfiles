#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <stdlib.h>
#include <unistd.h>

#include "input/option.h"

void redirect_all_stdout(void)
{
        cr_redirect_stdout();
        cr_redirect_stderr();
}

int error(void)
{
    write(2, "error", 5);
    exit(0);
}

Test(parse_options, is_c)
{
    // Given
    int count = 3;
    char *args[3] = {"exe", "-c", "echo success"};
    // When
    struct opt *option = parse_options(count, args);
    // Then
    cr_expect_not_null(option);
    cr_expect_eq(option->is_c, 1);
    cr_expect_str_eq(option->c_string, args[2]);
    free_options(option);
}

Test(parse_options, minus_O_ast_print)
{
    // Given
    int count = 3;
    char *args[4] = {"exe", "-O", "ast_print", NULL};
    // When
    struct opt *option = parse_options(count, args);
    // Then
    cr_expect_not_null(option);
    cr_expect_eq(option->is_c, 0);
    cr_expect_eq(option->is_norc, 0);
    cr_expect_eq(option->is_ast_print, 0);
    for (int i = 0; i < 8; i++)
    {
        if (i == 0)
            cr_expect_eq(option->shopt[0], 1);
        else
            cr_expect_eq(option->shopt[i], 0);
    }
    free_options(option);
}

Test(parse_options, minus_O_xpg_echo)
{
    // Given
    int count = 3;
    char *args[4] = {"exe", "-O", "xpg_echo", NULL};
    // When
    struct opt *option = parse_options(count, args);
    // Then
    cr_expect_not_null(option);
    cr_expect_eq(option->is_c, 0);
    cr_expect_eq(option->is_norc, 0);
    cr_expect_eq(option->is_ast_print, 0);
    for (int i = 0; i < 8; i++)
    {
        if (i == 7)
            cr_expect_eq(option->shopt[7], 1);
        else
            cr_expect_eq(option->shopt[i], 0);
    }
    free_options(option);
}

Test(parse_options, plus_O_extglob)
{
    // Given
    int count = 3;
    char *args[4] = {"exe", "+O", "extglob", NULL};
    // When
    struct opt *option = parse_options(count, args);
    // Then
    cr_expect_not_null(option);
    cr_expect_eq(option->is_c, 0);
    cr_expect_eq(option->is_norc, 0);
    cr_expect_eq(option->is_ast_print, 0);
    for (int i = 0; i < 8; i++)
    {
        if (i == 3)
            cr_expect_eq(option->shopt[3], -1);
        else
            cr_expect_eq(option->shopt[i], 0);
    }
    free_options(option);
}

Test(parse_options, minus_O_false, .exit_code = 2, .init=redirect_all_stdout)
{
    // Given
    int count = 3;
    char *args[4] = {"exe", "-O", "false", NULL};
    // When
    struct opt *option = parse_options(count, args);
    // Then
    free_options(option);
}

Test(parse_options, many_hardcore_options)
{
    // Given
    int count = 12;
    char *args[13] =
    {
        "exe", "+O", "extglob", "-O", "extglob", "--ast-print",
        "+O", "sourcepath", "-c", "ls -la", "-O", "nocaseglob", NULL
    };
    // When
    struct opt *option = parse_options(count, args);
    // Then
    cr_expect_not_null(option);
    cr_expect_eq(option->is_ast_print, 1);
    cr_expect_eq(option->is_norc, 0);
    cr_expect_eq(option->is_c, 1);
    cr_expect_str_eq(option->c_string, "ls -la");

    cr_expect_eq(option->shopt[0], 0);
    cr_expect_eq(option->shopt[1], 0);
    cr_expect_eq(option->shopt[2], 0);
    cr_expect_eq(option->shopt[3], 1);
    cr_expect_eq(option->shopt[4], 1);
    cr_expect_eq(option->shopt[5], 0);
    cr_expect_eq(option->shopt[6], -1);
    cr_expect_eq(option->shopt[7], 0);

    free_options(option);
}
