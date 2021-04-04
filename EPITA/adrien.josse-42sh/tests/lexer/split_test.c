#include <criterion/criterion.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"
#include "lexer/split.h"

Test(next_word, multiple_word)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if pwd && ls");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    char *word = next_word(lexer, 0);

    // THEN
    cr_expect_str_eq(word, "if");
    free(word);
    word = next_word(lexer, 0);
    cr_expect_str_eq(word, "pwd");
    free(word);
    word = next_word(lexer, 0);
    cr_expect_str_eq(word, "&&");
    free(word);
    word = next_word(lexer, 0);
    cr_expect_str_eq(word, "ls");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, quote_word)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if \"pwd && ls\"");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    char *word = next_word(lexer, 0);

    // THEN
    cr_expect_str_eq(word, "if");
    free(word);
    word = next_word(lexer, 0);
    cr_expect_str_eq(word, "\"pwd && ls\"");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, softcore)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, " echo test \"; then i\"");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "echo");
    free(word);

    // WHEN
    word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "test");
    free(word);

    // WHEN
    word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "\"; then i\"");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, quoting_in_word)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "ech\"o tes\"t");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "ech\"o tes\"t");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, quoting_subshell)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "ech$(\"o tes\")t");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "ech$(\"o tes\")t");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, quoting_arithmetic)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "ech$((\"o tes\"))t");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "ech$((\"o tes\"))t");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, quoting_backslash)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "\" mon \\\" cul \\\" \"");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "\" mon \\\" cul \\\" \"");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, quoting_backslash_escape)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "\\$\\(\\)");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "\\$\\(\\)");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, quoting_in_subshell)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "$(( subshell ? \"))\" ))");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "$(( subshell ? \"))\" ))");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, quoting_multiple)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "ech\"o tes\"pour$(mon test)de`ma vie`");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "ech\"o tes\"pour$(mon test)de`ma vie`");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, subshell_in_subshell)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "$(echo $(3 + 4) done)");
    struct lexer *lexer = set_lexer(NULL);
    // WHEN
    char *word = next_word(lexer, 0);
    // THEN
    cr_expect_str_eq(word, "$(echo $(3 + 4) done)");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(next_word, empty)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    char *word = next_word(lexer, 0);

    // THEN
    cr_expect_str_eq(word, "");
    free(word);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
