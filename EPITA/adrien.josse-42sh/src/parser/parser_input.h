/**
** \file
** Root 'grammar' rules.
*/

#ifndef PARSER_INPUT_H
# define PARSER_INPUT_H

#include "lexer/lexer.h"

#include "parser/command.h"

/**
** Pipeline structure node as a linked list.
** Contains a COMMAND NODE linked list of at least one element.
*/
struct pipeline_node
{
    struct pipeline_node *next;
    int is_and;

    int is_not;

    struct command_node *command;
};

/**
** And_or structure node as a linked list.
** Contains a PIPELINE NODE linked list of at least one element.
** if ! is_and then is_or
*/
struct and_or_node
{
    struct and_or_node *next;

    int is_background;

    struct pipeline_node *pipeline;
};

/**
** List structure node.
** Contains a AND_OR NODE linked list of at least one element.
*/
struct list_node
{
    struct and_or_node *and_or;
};

/**
** Input structure node.
** Contains a LIST NODE linked list that can be NULL.
*/
struct input_node
{
    struct list_node *list;
    int is_done;
};

/*
** Creates INPUT NODE as the root of an AST.
** @param lexer The lexer structure.
** @return Returns INPUT NODE for AST.
*/
struct input_node *grammar_input(struct lexer *lexer);

/*
** Creates LIST NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns LIST NODE for AST.
*/
struct list_node *grammar_list(struct lexer *lexer);

/*
** Creates AND_OR NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns AND_OR NODE for AST.
*/
struct and_or_node *grammar_and_or(struct lexer *lexer);

/*
** Creates PIPELINE NODE to add in AST.
** @param lexer The lexer structure.
** @return Returns PIPELINE NODE for AST.
*/
struct pipeline_node *grammar_pipeline(struct lexer *lexer);

#endif /* ! PARSER_INPUT_H */
