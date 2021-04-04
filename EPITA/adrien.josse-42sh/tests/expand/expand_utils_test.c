#include <criterion/criterion.h>

#include "expand/expand_utils.h"

Test(expand_in_str, basic_expand)
{
    // WHEN
    char *str = strdup("echo $big_daddy");
    char *replaced = "$big_daddy";
    char *replacement = "sugar_daddy";

    // WHEN
    char *res = expand_in_str(str, replaced, replacement);

    // THEN
    cr_expect_str_eq(res, "echo sugar_daddy");

    free(res);
}

Test(expand_in_str, multiple_word_expand)
{
    // WHEN
    char *str = strdup("echo $big_mommy");
    char *replaced = "$big_mommy";
    char *replacement = "Ur mama is so fat ...";

    // WHEN
    char *res = expand_in_str(str, replaced, replacement);

    // THEN
    cr_expect_str_eq(res, "echo Ur mama is so fat ...");

    free(res);
}
