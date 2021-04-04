#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/loops.h"

#include "free/loops_free.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/* ---------- Do group tests ---------- */

Test(loops, do_group_working)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "do something; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct do_group_node *node = grammar_do_group(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->body);

    do_group_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, do_group_missing_do)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "something; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct do_group_node *node = grammar_do_group(lexer);

    // THEN
    cr_expect_null(node);

    do_group_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, do_group_missing_done, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "do something;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct do_group_node *node = grammar_do_group(lexer);

    cr_expect_null(node);

    do_group_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, do_group_missing_body, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "do done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct do_group_node *node = grammar_do_group(lexer);

    cr_expect_null(node);

    do_group_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- For rule tests ---------- */

Test(loops, rule_for_working)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "for i in seq 1 12; do echo; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_for_node *node = grammar_rule_for(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_str_eq(node->iterator, "i");
    cr_expect_not_null(node->iterated);
    cr_expect_str_eq(node->iterated[0], "seq");
    cr_expect_str_eq(node->iterated[1], "1");
    cr_expect_str_eq(node->iterated[2], "12");
    cr_expect_not_null(node->body);

    rule_for_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_for_working_no_in_iterated)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "for i in; do echo; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_for_node *node = grammar_rule_for(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_str_eq(node->iterator, "i");
    cr_expect_null(node->iterated);
    cr_expect_not_null(node->body);

    rule_for_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_for_working_no_in)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "for i; do echo; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_for_node *node = grammar_rule_for(lexer);

    // THEN
    cr_expect_not_null(node);

    rule_for_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_for_no_for)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "i in 12; do echo; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_for_node *node = grammar_rule_for(lexer);

    // THEN
    cr_expect_null(node);

    rule_for_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_for_no_iterator, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "for in stuff; do echo; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_for_node *node = grammar_rule_for(lexer);

    cr_expect_null(node);

    rule_for_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_for_no_do, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "for i in stuff; echo; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_for_node *node = grammar_rule_for(lexer);

    cr_expect_null(node);

    rule_for_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_for_nothing_after_for, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "for; do echo; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_for_node *node = grammar_rule_for(lexer);

    cr_expect_null(node);

    rule_for_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_for_no_body, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "for i; do; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_for_node *node = grammar_rule_for(lexer);

    cr_expect_null(node);

    rule_for_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- While rule tests ---------- */

Test(loops, rule_while_working)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "while false; do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_while_node *node = grammar_rule_while(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->condition);
    cr_expect_not_null(node->body);

    rule_while_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_while_no_body, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "while false; do ; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_while_node *node = grammar_rule_while(lexer);

    cr_expect_null(node);

    rule_while_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_while_no_condition, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "while; do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_while_node *node = grammar_rule_while(lexer);

    cr_expect_null(node);

    rule_while_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_while_missing_break, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "while false do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_while_node *node = grammar_rule_while(lexer);

    cr_expect_null(node);

    rule_while_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_while_no_do, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "while false; pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_while_node *node = grammar_rule_while(lexer);

    cr_expect_null(node);

    rule_while_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_while_no_while)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "false; do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_while_node *node = grammar_rule_while(lexer);

    // THEN
    cr_expect_null(node);

    rule_while_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Until rule tests ---------- */

Test(loops, rule_until_working)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "until true; do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_until_node *node = grammar_rule_until(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->condition);
    cr_expect_not_null(node->body);

    rule_until_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_until_no_body, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "until true; do ; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_until_node *node = grammar_rule_until(lexer);

    cr_expect_null(node);

    rule_until_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_until_no_condition, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "until; do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_until_node *node = grammar_rule_until(lexer);

    cr_expect_null(node);

    rule_until_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_until_missing_break, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "until true do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_until_node *node = grammar_rule_until(lexer);

    cr_expect_null(node);

    rule_until_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_until_no_do, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "until true; pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_until_node *node = grammar_rule_until(lexer);

    cr_expect_null(node);

    rule_until_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(loops, rule_until_no_until)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "true; do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_until_node *node = grammar_rule_until(lexer);

    // THEN
    cr_expect_null(node);

    rule_until_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
