#include <criterion/criterion.h>
#include <readline/readline.h>
#include <criterion/redirect.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/redirection.h"
#include "parser/simple_command.h"

#include "free/redirection_free.h"
#include "free/simple_command_free.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/* ---------- Redirection node tests ----------  */

Test(redirection, redirection_valid_great_string)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "3> foo");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct redirection_node *node = grammar_redirection(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->ionumber, 3);
    cr_expect_eq(node->op, GREAT);
    cr_expect_str_eq(node->redirect_out, "foo");

    redirection_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(redirection, redirection_valid_clobber_string)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "12>| 2w9103rf");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct redirection_node *node = grammar_redirection(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->ionumber, 12);
    cr_expect_eq(node->op, CLOBBER);
    cr_expect_str_eq(node->redirect_out, "2w9103rf" );

    redirection_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(redirection, redirection_valid_less_string)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "1000< 2..4=+@8");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct redirection_node *node = grammar_redirection(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->ionumber, 1000);
    cr_expect_eq(node->op, LESS);
    cr_expect_str_eq(node->redirect_out, "2..4=+@8" );

    redirection_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(redirection, redirection_valid_greatand_string)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "909>&1");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct redirection_node *node = grammar_redirection(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->ionumber, 909);
    cr_expect_eq(node->op, GREATAND);
    cr_expect_str_eq(node->redirect_out, "1");

    redirection_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(redirection, redirection_valid_string_without_ionumber)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "<<ok\nboomers\nok");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct redirection_node *node = grammar_redirection(lexer);
    token_free(pop(lexer));
    peek(lexer, 0);

    // THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->ionumber, -1);
    cr_expect_eq(node->op, DLESS);
    cr_expect_str_eq(node->redirect_out, "boomers\n");

    redirection_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(redirection, redirection_invalid_string, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "toto=titi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct redirection_node *node = grammar_redirection(lexer);

    // THEN
    cr_expect_null(node);

    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Prefix node tests ----------  */

Test(redirection, prefix_assignment_word)
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

Test(redirection, prefix_redirection_string)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "<<echo\nboomers\necho");
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
    cr_expect_str_eq(node->content.redirect->redirect_out, "boomers\n");

    prefix_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(redirection, prefix_word)
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

Test(redirection, element_word)
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

Test(redirection, element_redirection_string)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "<<sayonara\nfken zoomers\nsayonara");
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
    cr_expect_str_eq(node->content.redirect->redirect_out, "fken zoomers\n");

    element_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
