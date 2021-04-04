/**
** \file
** Execution of the root nodes of the AST.
*/
#ifndef EXEC_INPUT_H
#define EXEC_INPUT_H

#include "input/env.h"

#include "parser/parser_input.h"

/**
** Execution of the INPUT NODE as root of the AST.
** @param input The INPUT NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_input(struct input_node *input, struct env *env);

/**
** Execution of the LIST NODE in AST.
** @param list The LIST NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_list(struct list_node *list, struct env *env);

/**
** Execution of the AND_OR NODE in AST.
** @param and_or The AND_OR NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_and_or(struct and_or_node *and_or, struct env *env);

/**
** Execution of the PIPELINE NODE in AST.
** @param pipeline The PIPELINE NODE to execute.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int exec_pipeline(struct pipeline_node *pipeline, struct env *env);

#endif /* ! EXEC_H */
