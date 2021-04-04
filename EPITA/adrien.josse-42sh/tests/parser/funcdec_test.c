#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/funcdec.h"

#include "free/funcdec_free.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(rule_funcdec, inline_funcdec)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "hello_world () { echo 'hello, world';}");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct funcdec_node *node = grammar_funcdec(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_str_eq("hello_world", node->name);
    cr_expect_not_null(node->body);

    funcdec_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_funcdec, basic_funcdec)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "hello_world () { \n\techo 'hello, world' \n}");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct funcdec_node *node = grammar_funcdec(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_str_eq("hello_world", node->name);
    cr_expect_not_null(node->body);

    funcdec_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_funcdec, complex_funcdec)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "function myFunc () {\n\tif true; then\n\t\tls;\n\telse\n\t\ttree;\n\tfi\n}");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct funcdec_node *node = grammar_funcdec(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_str_eq("myFunc", node->name);
    cr_expect_not_null(node->body);

    funcdec_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_funcdec, function_word_funcdec)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "function sixnine () {\n factor 69\n}");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct funcdec_node *node = grammar_funcdec(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_str_eq("sixnine", node->name);
    cr_expect_not_null(node->body);

    funcdec_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_funcdec, empty_function, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "function sixnine () {}");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct funcdec_node *node = grammar_funcdec(lexer);

    // THEN
    cr_expect_null(node);

    funcdec_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_funcdec, function_misspelled, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "functoin sixnine () {\n factor 69\n}");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct funcdec_node *node = grammar_funcdec(lexer);

    // THEN
    cr_expect_null(node);

    funcdec_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_funcdec, invalid_str, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "tree");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct funcdec_node *node = grammar_funcdec(lexer);

    // THEN
    cr_expect_null(node);

    funcdec_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(rule_funcdec, invalid_func_name, .init=redirect_all_stdout)
{
    // GIVEN
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "then () {\n factor 69\n}");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct funcdec_node *node = grammar_funcdec(lexer);

    // THEN
    cr_expect_null(node);

    funcdec_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
