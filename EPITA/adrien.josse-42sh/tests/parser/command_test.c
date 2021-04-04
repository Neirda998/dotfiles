#include <criterion/criterion.h>
#include <readline/readline.h>

#include "input/input.h"

#include "lexer/lexer.h"

#include "parser/command.h"
#include "parser/simple_command.h"

#include "free/command_free.h"

/* ---------- Shell command tests ---------- */

Test(command, shell_command_braces_compound_list_break)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "{ ls;}");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct shell_command_node *node = grammar_shell_command(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, CPD_LST_BRK);
    cr_expect_not_null(node->value.cpd_lst_brk);

    shell_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(command, shell_command_parenthesis_compound_list)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "(ls)");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct shell_command_node *node = grammar_shell_command(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, CPD_LST);
    cr_expect_not_null(node->value.cpd_lst);

    shell_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(command, shell_command_rule_for)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "for i in seq 1 12; do echo; done");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct shell_command_node *node = grammar_shell_command(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, RULE_FOR);
    cr_expect_not_null(node->value.rule_for);

    shell_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(command, shell_command_rule_while)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "while false; do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct shell_command_node *node = grammar_shell_command(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, RULE_WHILE);
    cr_expect_not_null(node->value.rule_while);

    shell_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(command, shell_command_rule_until)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "until true; do pwd; done;");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct shell_command_node *node = grammar_shell_command(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, RULE_UNTIL);
    cr_expect_not_null(node->value.rule_until);

    shell_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(command, shell_command_rule_case)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case i in i) echo i; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct shell_command_node *node = grammar_shell_command(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, RULE_CASE);
    cr_expect_not_null(node->value.rule_case);

    shell_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(command, shell_command_rule_if)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "if true; then ls; fi");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct shell_command_node *node = grammar_shell_command(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_eq(node->type, RULE_IF);
    cr_expect_not_null(node->value.rule_if);

    shell_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(command, shell_command_not_working)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "stuff");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct shell_command_node *node = grammar_shell_command(lexer);

    //THEN
    cr_expect_null(node);

    shell_command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

/* ---------- Command tests ---------- */

Test(command, command_case)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "case i in i) echo i; esac");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct command_node *node = grammar_command(lexer);

    //THEN
    cr_expect_not_null(node);
    cr_expect_null(node->simple_command);
    cr_expect_not_null(node->shell_command);
    cr_expect_null(node->next);

    command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}

Test(command, command_simple_command)
{
    FILE *rl_backup = rl_instream;
    rl_instream = open_input(1, "echo gateau");
    struct lexer *lexer = set_lexer(NULL);

    // WHEN
    struct command_node *node = grammar_command(lexer);

    // THEN
    cr_expect_not_null(node);
    cr_expect_not_null(node->simple_command);

    command_node_free(node);
    unset_lexer(lexer);
    close_input(rl_instream);
    rl_instream = rl_backup;
}
