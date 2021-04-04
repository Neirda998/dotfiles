#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/parser_input.h"

#include "free/parser_input_free.h"
#include "free/funcdec_free.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/* ---------- Input tests ---------- */

Test(grammar_input, input_is_done)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "echo command");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct input_node *input = grammar_input(lexer);

    //THEN
    cr_expect_not_null(input);
    cr_expect_not_null(input->list);
    cr_expect_eq(input->is_done, 1);

    input_node_free(input);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_input, input_isnt_done)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "ls\n");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct input_node *input = grammar_input(lexer);

    //THEN
    cr_expect_not_null(input);
    cr_expect_not_null(input->list);
    cr_expect_eq(input->is_done, 0);

    input_node_free(input);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_input, funcdec_with_new_line)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "hello_world () { echo 'hello, world';}\n");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct input_node *input = grammar_input(lexer);

    //THEN
    cr_expect_not_null(input);
    cr_expect_not_null(input->list);
    cr_expect_eq(input->is_done, 0);

    funcdec_node_free(input->list->and_or->pipeline->command->funcdec);
    input_node_free(input);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_input, invalid_input, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, ";");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct input_node *input = grammar_input(lexer);

    //THEN
    cr_expect_null(input);

    input_node_free(input);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- List tests ---------- */

Test(grammar_list, single_list)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "ls");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct list_node *list = grammar_list(lexer);

    //THEN
    cr_expect_not_null(list);
    cr_expect_not_null(list->and_or);
    cr_expect_null(list->and_or->next);

    list_node_free(list);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_list, multiple_semi_list)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "tree; pwd");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct list_node *list = grammar_list(lexer);

    //THEN
    cr_expect_not_null(list);
    cr_expect_not_null(list->and_or);
    cr_expect_not_null(list->and_or->next);
    cr_expect_null(list->and_or->next->next);

    list_node_free(list);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_list, multiple_and_list)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "test & ls");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct list_node *list = grammar_list(lexer);

    //THEN
    cr_expect_not_null(list);
    cr_expect_not_null(list->and_or);
    cr_expect_not_null(list->and_or->next);
    cr_expect_null(list->and_or->next->next);

    list_node_free(list);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_list, invalid_list, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "||");
    struct lexer *lexer = set_lexer(NULL);

    //WHEN
    struct list_node *list = grammar_list(lexer);

    //THEN
    cr_expect_null(list);

    list_node_free(list);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- And_or tests ---------- */

Test(grammar_and_or, simple_str)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "test");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct and_or_node *and_or = grammar_and_or(lexer);

    // THEN
    cr_expect_not_null(and_or);
    cr_expect_not_null(and_or->pipeline);
    cr_expect_eq(and_or->is_background, 0);
    cr_expect_null(and_or->next);

    and_or_node_free(and_or);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_and_or, multiple_and_if_str)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "test && stuff");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct and_or_node *and_or = grammar_and_or(lexer);

    // THEN
    cr_expect_not_null(and_or);
    cr_expect_not_null(and_or->pipeline);
    cr_expect_eq(and_or->is_background, 0);
    cr_expect_eq(and_or->pipeline->is_and, 0);
    cr_expect_not_null(and_or->pipeline->next);
    cr_expect_eq(and_or->pipeline->next->is_and, 1);
    cr_expect_null(and_or->pipeline->next->next);

    and_or_node_free(and_or);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_and_or, multiple_or_if_str)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, " ! test || stuff");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct and_or_node *and_or = grammar_and_or(lexer);

    // THEN
    cr_expect_not_null(and_or);
    cr_expect_not_null(and_or->pipeline);
    cr_expect_eq(and_or->is_background, 0);
    cr_expect_eq(and_or->pipeline->is_and, 0);
    cr_expect_eq(and_or->pipeline->is_not, 1);
    cr_expect_not_null(and_or->pipeline->next);
    cr_expect_eq(and_or->pipeline->next->is_and, 0);
    cr_expect_null(and_or->pipeline->next->next);

    and_or_node_free(and_or);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_and_or, invalid_str, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "then");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct and_or_node *and_or = grammar_and_or(lexer);

    // THEN
    cr_expect_null(and_or);

    and_or_node_free(and_or);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Pipeline tests ---------- */

Test(grammar_pipeline, simple_str)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "tree");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct pipeline_node *pipeline = grammar_pipeline(lexer);

    // THEN
    cr_expect_not_null(pipeline);
    cr_expect_null(pipeline->next);
    cr_expect_eq(pipeline->is_and, 0);
    cr_expect_eq(pipeline->is_not, 0);
    cr_expect_not_null(pipeline->command);
    cr_expect_null(pipeline->command->next);

    pipeline_node_free(pipeline);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_pipeline, simple_not_str)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "! tree");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct pipeline_node *pipeline = grammar_pipeline(lexer);

    // THEN
    cr_expect_not_null(pipeline);
    cr_expect_null(pipeline->next);
    cr_expect_eq(pipeline->is_and, 0);
    cr_expect_eq(pipeline->is_not, 1);
    cr_expect_not_null(pipeline->command);
    cr_expect_null(pipeline->command->next);

    pipeline_node_free(pipeline);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_pipeline, multiple_str)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "tree | grep");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct pipeline_node *pipeline = grammar_pipeline(lexer);

    // THEN
    cr_expect_not_null(pipeline);
    cr_expect_null(pipeline->next);
    cr_expect_eq(pipeline->is_and, 0);
    cr_expect_eq(pipeline->is_not, 0);
    cr_expect_not_null(pipeline->command);
    cr_expect_not_null(pipeline->command->next);
    cr_expect_null(pipeline->command->next->next);

    pipeline_node_free(pipeline);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(grammar_pipeline, invalid_str, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "then");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct pipeline_node *pipeline = grammar_pipeline(lexer);

    // THEN
    cr_expect_null(pipeline);

    pipeline_node_free(pipeline);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
