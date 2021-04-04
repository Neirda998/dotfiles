#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/if.h"

#include "free/if_free.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(rule_if, basic_if)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if true; then ls; fi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_if_node *node = grammar_rule_if(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->condition);
    cr_expect_not_null(node->body);

    rule_if_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_if, basic_if_else)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if true; then ls; else tree; fi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_if_node *node = grammar_rule_if(lexer);

    // THEN
    cr_expect_not_null(node);

    rule_if_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_if, basic_if_elif_else)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if true;then ls;elif ls;then ls;else ls;fi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_if_node *node = grammar_rule_if(lexer);

    // THEN
    cr_expect_not_null(node);

    rule_if_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_if, no_condition, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if; then ls; else tree; fi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_if_node *node = grammar_rule_if(lexer);

    cr_expect_null(node);

    rule_if_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_if, no_body, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if true; then; fi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_if_node *node = grammar_rule_if(lexer);

    cr_expect_null(node);

    rule_if_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_if, no_then, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if true; ls; fi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_if_node *node = grammar_rule_if(lexer);

    cr_expect_null(node);

    rule_if_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_if, no_fi, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if true; then ls;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_if_node *node = grammar_rule_if(lexer);

    cr_expect_null(node);

    rule_if_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
