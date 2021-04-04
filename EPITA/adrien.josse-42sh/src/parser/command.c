#include <err.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "utils/memory.h"

#include "lexer/token.h"

#include "parser/case.h"
#include "parser/command.h"
#include "parser/compound_list.h"
#include "parser/if.h"
#include "parser/loops.h"
#include "parser/redirection.h"
#include "parser/simple_command.h"

#include "free/command_free.h"
#include "free/compound_list_free.h"

static struct shell_command_node *set_sh_cmd_cpd_lst_brk(
                    struct lexer *lexer,
                    struct shell_command_node *shell_command)
{
    token_free(pop(lexer));
    shell_command->type = CPD_LST_BRK;
    shell_command->value.cpd_lst_brk = grammar_compound_list_break(lexer);

    if (!shell_command->value.cpd_lst_brk)
    {
        //compound_list_break_node_free(shell_command->value.cpd_lst_brk);
        shell_command_node_free(shell_command);
        warnx("syntax error : expected body after '{'");
        return NULL;
    }

    struct token *token = peek(lexer, 0);
    if (token->type != RESERVED || token->value.res != Rbrace)
    {
        //compound_list_break_node_free(shell_command->value.cpd_lst_brk);
        shell_command_node_free(shell_command);
        warnx("syntax error : expected '}'");
        return NULL;
    }
    token_free(pop(lexer));

    return shell_command;
}

static struct shell_command_node *set_sh_cmd_cpd_lst(
                    struct lexer *lexer,
                    struct shell_command_node *shell_command)
{
    token_free(pop(lexer));
    shell_command->type = CPD_LST;
    shell_command->value.cpd_lst = grammar_compound_list(lexer);

    if (!shell_command->value.cpd_lst)
    {
        //compound_list_node_free(shell_command->value.cpd_lst);
        shell_command_node_free(shell_command);
        warnx("syntax error : expected body after '('");
        return NULL;
    }

    struct token *token = peek(lexer, 0);
    if (token->type != OPERATOR || token->value.op != R_PARENTHESIS)
    {
        //compound_list_node_free(shell_command->value.cpd_lst);
        shell_command_node_free(shell_command);
        warnx("syntax error : expected ')'");
        return NULL;
    }
    token_free(pop(lexer));

    return shell_command;
}

struct shell_command_node *grammar_shell_command(struct lexer *lexer)
{
    struct shell_command_node *shell_command =
        xcalloc(1, sizeof(struct shell_command_node));

    struct token *token = peek(lexer, 0);
    if (token->type == RESERVED && token->value.res == Lbrace)
        return set_sh_cmd_cpd_lst_brk(lexer, shell_command);

    if (token->type == OPERATOR && token->value.op == L_PARENTHESIS)
        return set_sh_cmd_cpd_lst(lexer, shell_command);


    shell_command->value.rule_for = grammar_rule_for(lexer);
    if (shell_command->value.rule_for)
    {
        shell_command->type = RULE_FOR;
        return shell_command;
    }

    shell_command->value.rule_while = grammar_rule_while(lexer);
    if (shell_command->value.rule_while)
    {
        shell_command->type = RULE_WHILE;
        return shell_command;
    }

    shell_command->value.rule_until = grammar_rule_until(lexer);
    if (shell_command->value.rule_until)
    {
        shell_command->type = RULE_UNTIL;
        return shell_command;
    }

    shell_command->value.rule_case = grammar_rule_case(lexer);
    if (shell_command->value.rule_case)
    {
        shell_command->type = RULE_CASE;
        return shell_command;
    }

    shell_command->value.rule_if = grammar_rule_if(lexer);
    if (shell_command->value.rule_if)
    {
        shell_command->type = RULE_IF;
        return shell_command;
    }
    free(shell_command);
    return NULL;
}

static void add_redirections(struct command_node *command, struct lexer *lexer)
{
    struct redirection_node *new_redir = grammar_redirection(lexer);
    while (new_redir)
    {
        command->redirections = xrealloc(command->redirections,
                                         sizeof(*new_redir)
                                         * (command->redir_len + 1));
        command->redirections[command->redir_len++] = new_redir;
        new_redir = grammar_redirection(lexer);
    }
}

struct command_node *grammar_command(struct lexer *lexer)
{
    struct command_node *command = xcalloc(1, sizeof(struct command_node));

    command->shell_command = grammar_shell_command(lexer);
    if (command->shell_command)
    {
        add_redirections(command, lexer);
        return command;
    }

    command->funcdec = grammar_funcdec(lexer);
    if (command->funcdec)
    {
        add_redirections(command, lexer);
        return command;
    }

    command->simple_command = grammar_simple_command(lexer);
    if (command->simple_command)
        return command;

    command_node_free(command);
    return NULL;
}
