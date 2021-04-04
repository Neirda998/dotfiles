#include <criterion/criterion.h>
#include <readline/readline.h>

#include "input/input.h"

#include "parser/compound_list.h"

#include "free/compound_list_free.h"

/* ---------- Compound list break tests ---------- */

Test(compound_list, compound_list_break_simple)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "ls;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct compound_list_break_node *node = grammar_compound_list_break(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or_nodes);
    cr_expect_null(node->and_or_nodes->next);

    compound_list_break_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(compound_list, compound_list_break_double)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "pwd & tree");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct compound_list_break_node *node = grammar_compound_list_break(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or_nodes);
    cr_expect_not_null(node->and_or_nodes->next);
    cr_expect_null(node->and_or_nodes->next->next);

    compound_list_break_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(compound_list, compound_list_break_triple)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "pwd & tree ; ls");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct compound_list_break_node *node = grammar_compound_list_break(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or_nodes);
    cr_expect_not_null(node->and_or_nodes->next);
    cr_expect_not_null(node->and_or_nodes->next->next);
    cr_expect_null(node->and_or_nodes->next->next->next);

    compound_list_break_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(compound_list, compound_list_break_backslash_n)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "pwd & tree\n");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct compound_list_break_node *node = grammar_compound_list_break(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or_nodes);
    cr_expect_not_null(node->and_or_nodes->next);
    cr_expect_null(node->and_or_nodes->next->next);

    compound_list_break_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(compound_list, compound_list_break_backslash_begin)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, " \n pwd & tree\n");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct compound_list_break_node *node = grammar_compound_list_break(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or_nodes);
    cr_expect_not_null(node->and_or_nodes->next);
    cr_expect_null(node->and_or_nodes->next->next);

    compound_list_break_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Compound list tests ---------- */

Test(compound_list, compound_list_simple)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "pwd");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct compound_list_node *node = grammar_compound_list(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or_nodes);
    cr_expect_null(node->and_or_nodes->next);

    compound_list_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(compound_list, compound_list_double)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "pwd & tree");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct compound_list_node *node = grammar_compound_list(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or_nodes);
    cr_expect_not_null(node->and_or_nodes->next);
    cr_expect_null(node->and_or_nodes->next->next);

    compound_list_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(compound_list, compound_list_triple)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "pwd & tree ; ls");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct compound_list_node *node = grammar_compound_list(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->and_or_nodes);
    cr_expect_not_null(node->and_or_nodes->next);
    cr_expect_not_null(node->and_or_nodes->next->next);
    cr_expect_null(node->and_or_nodes->next->next->next);

    compound_list_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
