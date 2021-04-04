/**
** \file
** Grammar 'command' rules.
*/

#ifndef COMMAND_H
# define COMMAND_H

#include "lexer/lexer.h"

#include "parser/simple_command.h"
#include "parser/funcdec.h"

/**
** Enumeration of all shell command types.
*/
enum sh_cmd_type
{
    CPD_LST_BRK = 0,
    CPD_LST,
    RULE_FOR,
    RULE_WHILE,
    RULE_UNTIL,
    RULE_CASE,
    RULE_IF
};

/**
** Shell command union.
** Contains the shell command child node.
*/
union sh_cmd_union
{
    struct compound_list_break_node *cpd_lst_brk; ///< compound_list_break node
    struct compound_list_node *cpd_lst;           ///< compound_list_node
    struct rule_for_node *rule_for;               ///< rule_for node
    struct rule_while_node *rule_while;           ///< rule_while node
    struct rule_until_node *rule_until;           ///< rule_until node
    struct rule_case_node *rule_case;             ///< rule_case node
    struct rule_if_node *rule_if;                 ///< rule_if node
};

/**
** Command structure node.
** Contains a shell_command union and its type.
*/
struct shell_command_node
{
    enum sh_cmd_type type;    ///< type of the shell command
    union sh_cmd_union value; ///< value of the shell command
};

/**
** Command structure node.
** Contains a SIMPLE COMMAND NODE that can be NULL.
** Contains a SHELL COMMAND NODE that can be NULL.
** Contains a FUNCDEC NODE that can be NULL.
** Contains a list of REDIRECTION NODE that can be NULL.
*/

struct command_node
{
    struct command_node *next;

    struct simple_command_node *simple_command;
    struct shell_command_node *shell_command;
    struct funcdec_node *funcdec;
    int redir_len;
    struct redirection_node **redirections;
};

/**
** Creates SHELL COMMAND NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns SHELL COMMAND NODE for AST.
*/
struct shell_command_node *grammar_shell_command(struct lexer *lexer);

struct fundec_node *grammar_fundec(struct lexer *lexer);

/**
** Creates COMMAND NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns COMMAND NODE for AST.
*/
struct command_node *grammar_command(struct lexer *lexer);

#endif /* ! COMMAND_H */
