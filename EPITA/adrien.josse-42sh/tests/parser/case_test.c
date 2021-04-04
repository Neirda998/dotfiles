#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/case.h"
#include "parser/parser_input.h"

#include "free/case_free.h"
#include "free/parser_input_free.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/* ---------- Case item testing ---------- */

Test(rule_case, case_item)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "i) echo i");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct case_item_node *node = grammar_case_item(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_null(node->next);
    cr_expect_eq(node->size, 1);
    cr_expect_str_eq(node->patterns[0], "i");
    cr_expect_not_null(node->statement);

    case_item_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_case, both_parenthesis)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "(i) echo i");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct case_item_node *node = grammar_case_item(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_null(node->next);
    cr_expect_eq(node->size, 1);
    cr_expect_str_eq(node->patterns[0], "i");
    cr_expect_not_null(node->statement);

    case_item_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_case, multiples_case_items)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "i|j|k) echo i");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct case_item_node *node = grammar_case_item(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_null(node->next);
    cr_expect_eq(node->size, 3);
    cr_expect_str_eq(node->patterns[0], "i");
    cr_expect_str_eq(node->patterns[1], "j");
    cr_expect_str_eq(node->patterns[2], "k");
    cr_expect_not_null(node->statement);

    case_item_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_case, missing_parenthesis, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "i echo i");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct case_item_node *node = grammar_case_item(lexer);

    cr_expect_null(node);

    case_item_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Case clause testing ---------- */

Test(rule_case, case_clause)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "i) echo i");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct case_clause_node *node = grammar_case_clause(lexer);

    // THEN
    cr_expect_not_null(node);

    case_clause_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_case, case_clause_both_parenthesis)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "(i) echo i");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct case_clause_node *node = grammar_case_clause(lexer);

    // THEN
    cr_expect_not_null(node);

    case_clause_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_case, case_clause_multiples_case_items)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "i|j|k) echo i");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct case_clause_node *node = grammar_case_clause(lexer);

    // THEN
    cr_expect_not_null(node);

    case_clause_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_case, case_clause_missing_parenthesis, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "i echo i");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct case_clause_node *node = grammar_case_clause(lexer);

    cr_expect_null(node);

    case_clause_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Full case testing ---------- */

Test(rule_case, easy_case)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case i in i) echo i; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_case_node *node = grammar_rule_case(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_str_eq(node->expression, "i");
    cr_expect_not_null(node->case_clause);

    rule_case_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_case, longer_case)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case toto in i) echo i;; s) echo s;; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_case_node *node = grammar_rule_case(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_str_eq(node->expression, "toto");
    cr_expect_not_null(node->case_clause);

    rule_case_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_case, missing_dsemi, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case toto in i) echo i s) echo s;; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct rule_case_node *node = grammar_rule_case(lexer);

    cr_expect_null(node);

    rule_case_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Input tests ---------- */

Test(parser_input, input_case)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case i in i) echo i; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct input_node *node = grammar_input(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->list);
    cr_expect_eq(node->is_done, 1);

    input_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- List tests ---------- */

Test(parser_input, list_case)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case i in i) echo i; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct list_node *node = grammar_list(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or);

    list_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- And_or tests ---------- */

Test(parser_input, and_or_case)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case i in i) echo i; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct and_or_node *node = grammar_and_or(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->is_background, 0);
    cr_expect_not_null(node->pipeline);
    cr_expect_null(node->next);

    and_or_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Pipeline tests ---------- */

Test(parser_input, pipeline_case)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case i in i) echo i; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct pipeline_node *node = grammar_pipeline(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->is_and, 0);
    cr_expect_eq(node->is_not, 0);
    cr_expect_not_null(node->command);
    cr_expect_null(node->next);

    pipeline_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
