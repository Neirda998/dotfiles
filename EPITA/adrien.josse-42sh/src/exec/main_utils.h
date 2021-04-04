/**
** \file
** Header for utils functions.
*/

#pragma once

#include "input/env.h"
/**
** Run 42sh from stream.
** @param env The execution environment.
** @return Returns the error code of the execution.
*/
int run_in_stream(struct env *env);
