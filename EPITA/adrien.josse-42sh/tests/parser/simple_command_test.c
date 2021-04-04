#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/simple_command.h"

#include "free/simple_command_free.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/* ---------- Prefix node tests ----------  */

Test(grammar_prefix, prefix_assignment_word)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto=titi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct prefix_node *node = grammar_prefix(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, String);
    cr_expect_not_null(node->content.word);
    cr_expect_str_eq(node->content.word, "toto=titi");
    cr_expect_null(node->next);

    prefix_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_prefix, prefix_assignment_word_missing_left)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "=titi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct prefix_node *node = grammar_prefix(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, String);
    cr_expect_not_null(node->content.word);
    cr_expect_str_eq(node->content.word, "=titi");
    cr_expect_null(node->next);

    prefix_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_prefix, prefix_assignment_word_missing_right)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto=");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct prefix_node *node = grammar_prefix(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, String);
    cr_expect_not_null(node->content.word);
    cr_expect_str_eq(node->content.word, "toto=");
    cr_expect_null(node->next);

    prefix_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_prefix, prefix_redirection_string)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "6>|9");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct prefix_node *node = grammar_prefix(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, Redirection);
    cr_expect_not_null(node->content.redirect);
    cr_expect_eq(node->content.redirect->ionumber, 6);
    cr_expect_eq(node->content.redirect->op, CLOBBER);
    cr_expect_str_eq(node->content.redirect->redirect_out, "9");

    prefix_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_prefix, prefix_redirection_string_missing_left)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "<<heredoc\nje suis\nheredoc");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct prefix_node *node = grammar_prefix(lexer);
    token_free(pop(lexer));
    peek(lexer, 0);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, Redirection);
    cr_expect_not_null(node->content.redirect);
    cr_expect_eq(node->content.redirect->ionumber, -1);
    cr_expect_eq(node->content.redirect->op, DLESS);
    cr_expect_str_eq(node->content.redirect->redirect_out, "je suis\n");

    prefix_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_prefix, prefix_redirection_string_missing_right, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "1>");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct prefix_node *node = grammar_prefix(lexer);

    // THEN
    cr_expect_null(node);

    prefix_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_prefix, error_prefix_word)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct prefix_node *node = grammar_prefix(lexer);

    // THEN
    cr_expect_null(node);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Element node tests ----------  */

Test(grammar_element, element_word)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct element_node *node = grammar_element(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, String);
    cr_expect_not_null(node->content.word);
    cr_expect_str_eq(node->content.word, "toto");
    cr_expect_null(node->next);

    element_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_element, element_redirection_string)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "6>|9");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct element_node *node = grammar_element(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, Redirection);
    cr_expect_not_null(node->content.redirect);
    cr_expect_eq(node->content.redirect->ionumber, 6);
    cr_expect_eq(node->content.redirect->op, CLOBBER);
    cr_expect_str_eq(node->content.redirect->redirect_out, "9");

    element_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_element, element_redirection_string_missing_left)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "<<heredoc\nje suis\nun\nheredoc\n");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct element_node *node = grammar_element(lexer);
    token_free(pop(lexer));
    peek(lexer, 0);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, Redirection);
    cr_expect_not_null(node->content.redirect);
    cr_expect_eq(node->content.redirect->ionumber, -1);
    cr_expect_eq(node->content.redirect->op, DLESS);
    cr_expect_str_eq(node->content.redirect->redirect_out, "je suis\nun\n");

    element_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_element, element_redirection_string_missing_right, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "1>");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct element_node *node = grammar_element(lexer);

    // THEN
    cr_expect_null(node);

    element_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Simple command tests ---------- */

Test(grammar_simple_command, simple_cmd_echo_num)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "echo 420");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct simple_command_node *node = grammar_simple_command(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->elements);
    cr_expect_str_eq(node->elements->content.word, "echo");
    cr_expect_not_null(node->elements->next);
    cr_expect_str_eq(node->elements->next->content.word, "420");
    cr_expect_null(node->elements->next->next);
    cr_expect_null(node->prefixes);

    simple_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_simple_command, simple_cmd_prefix_only)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "foo=baz");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct simple_command_node *node = grammar_simple_command(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->prefixes);
    cr_expect_str_eq(node->prefixes->content.word, "foo=baz");
    cr_expect_null(node->prefixes->next);
    cr_expect_null(node->elements);

    simple_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_simple_command, simple_cmd_prefixes_only)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto=tata titi=foo");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct simple_command_node *node = grammar_simple_command(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->prefixes);
    cr_expect_str_eq(node->prefixes->content.word, "toto=tata");
    cr_expect_not_null(node->prefixes->next);
    cr_expect_str_eq(node->prefixes->next->content.word, "titi=foo");
    cr_expect_null(node->prefixes->next->next);
    cr_expect_null(node->elements);

    simple_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_simple_command, simple_cmd_element_only)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct simple_command_node *node = grammar_simple_command(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_null(node->prefixes);
    cr_expect_not_null(node->elements);
    cr_expect_str_eq(node->elements->content.word, "toto");
    cr_expect_null(node->elements->next);

    simple_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_simple_command, simple_cmd_prefixes_elements)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto tata");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct simple_command_node *node = grammar_simple_command(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_null(node->prefixes);
    cr_expect_not_null(node->elements);
    cr_expect_str_eq(node->elements->content.word, "toto");
    cr_expect_not_null(node->elements->next);
    cr_expect_str_eq(node->elements->next->content.word, "tata");
    cr_expect_null(node->elements->next->next);

    simple_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_simple_command, simple_cmd_none)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "\n");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct simple_command_node *node = grammar_simple_command(lexer);

    // THEN
    cr_expect_null(node);

    simple_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_simple_command, simple_cmd_reserved_word)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "then");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct simple_command_node *node = grammar_simple_command(lexer);

    // THEN
    cr_expect_null(node);

    simple_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
