#include <criterion/criterion.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

Test(peek, simple_peek)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = peek(lexer, 0);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "toto");

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(peek, special_peek)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "\n");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = peek(lexer, 0);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(peek, pipe_peek)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "|");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = peek(lexer, 0);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, OPERATOR);
    cr_expect_eq(token->value.op, PIPE);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(peek, empty_peek)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token = peek(lexer, 0);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, END_OF_FILE);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ARCHIVED BECAUSE HEREDOCS ARE NO LONGER READ LIKE THIS
Test(pop, heredoc)
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "cannot the kin$gdom of S@lvation take;; me &> home? Key");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token = pop_heredoc(lexer, "Key");
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "cannot the kin$gdom of S@lvation take;; me &> home? ");

    token_free(token);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
*/

Test(pop, simple_pop)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "toto");

    token_free(token);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop, special_pop)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "\n");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);

    token_free(token);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop, and_no_space_pop)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "tst&ls");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "tst");
    token_free(token);

    //WHEN
    token = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, AND);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "ls");
    token_free(token);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}


Test(pop, redirection_pop)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "<3");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, OPERATOR);
    cr_expect_eq(token->value.op, LESS);
    token_free(token);

    //WHEN
    token = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, IO_NUMBER);
    cr_expect_str_eq(token->value.str, "3");
    token_free(token);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop, redirection_overflowing_ionumber)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "1000000000000000000>3");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct token *token = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "1000000000000000000");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, OPERATOR);
    cr_expect_eq(token->value.op, GREAT);
    token_free(token);

    //WHEN
    token = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, IO_NUMBER);
    cr_expect_str_eq(token->value.str, "3");
    token_free(token);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop, if_else_pop)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    char str[] = "if pwd && ls; then\n    cd\nelse\n    alias\nfi";
    rl_instream = open_input(1, str);
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct token *token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, RESERVED);
    cr_expect_eq(token->value.res, If);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "pwd");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, OPERATOR);
    cr_expect_eq(token->value.op, AND_IF);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "ls");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, SEMI);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, RESERVED);
    cr_expect_eq(token->value.res, Then);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "cd");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, RESERVED);
    cr_expect_eq(token->value.res, Else);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "alias");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, RESERVED);
    cr_expect_eq(token->value.res, Fi);
    token_free(token);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop, ignore_comments)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    char str[] = "if pwd && ls; then # BITCH LASAGNA\n    cd #echo fail\nelse\n    alias # or not\nfi";
    rl_instream = open_input(1, str);
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct token *token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, RESERVED);
    cr_expect_eq(token->value.res, If);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "pwd");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, OPERATOR);
    cr_expect_eq(token->value.op, AND_IF);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "ls");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, SEMI);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, RESERVED);
    cr_expect_eq(token->value.res, Then);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "cd");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, RESERVED);
    cr_expect_eq(token->value.res, Else);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "alias");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, RESERVED);
    cr_expect_eq(token->value.res, Fi);
    token_free(token);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop, mulitple_with_newlines)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    char str[] = " \n echo";
    rl_instream = open_input(1, str);
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct token *token = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, NEW_LINE);
    cr_expect_null(token->value.str);
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    printf("%d\n", token->type);
    //cr_expect_str_eq(token->value.str, "echo");
    token_free(token);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop_command, simple_pop_command)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "echo test blabla 420sh Blaze it");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = pop_command(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "echo");

    token_free(token);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop_command, special_pop_command)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "echo test then && ! {} if\n");
    struct lexer *lexer = set_lexer(NULL);
    //WHEN
    struct token *token  = pop_command(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "echo");

    token_free(token);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop_command, redir_pop_command)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "echo test 1>&2");
    struct lexer *lexer = set_lexer(NULL);

    struct token *token = pop_command(lexer);
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "echo");
    token_free(token);

    token = pop_command(lexer);
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "test");
    token_free(token);

    token = pop_command(lexer);
    cr_assert_not_null(token);
    cr_expect_eq(token->type, IO_NUMBER);
    cr_expect_str_eq(token->value.str, "1");
    token_free(token);

    token = pop_command(lexer);
    cr_assert_not_null(token);
    cr_expect_eq(token->type, OPERATOR);
    cr_expect_eq(token->value.op, GREATAND);
    token_free(token);

    token = pop_command(lexer);
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "2");
    token_free(token);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(pop_command, multiple_pop_command)
{
    //GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "echo test then && ! {} if\ntree random/dir .. test");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct token *token  = pop_command(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "echo");
    token_free(token);

    //WHEN
    token  = pop(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "test");
    token_free(token);

    //WHEN
    token  = pop_command(lexer);
    //THEN
    cr_assert_not_null(token);
    cr_expect_eq(token->type, WORD);
    cr_expect_str_eq(token->value.str, "then");
    token_free(token);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
