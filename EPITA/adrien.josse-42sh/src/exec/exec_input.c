#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "exec/exec_input.h"

#include "utils/fd_utils.h"
#include "utils/memory.h"

#include "parser/parser_input.h"
#include "parser/command.h"

#include "expand/variables.h"

#include "exec/exec_command.h"

int exec_input(struct input_node *input, struct env *env)
{
    if (!input)
        return 2;
    return exec_list(input->list, env);
}

int exec_list(struct list_node *list, struct env *env)
{
    if(!list)
        return 0;
    struct and_or_node *cur = list->and_or;
    int ret = 0;
    while (cur)
    {
        //if (cur->is_background)
        ret = exec_and_or(cur, env);
        cur = cur->next;
    }
    return ret;
}

int exec_and_or(struct and_or_node *and_or, struct env *env)
{
    struct pipeline_node *cur = and_or->pipeline;
    int ret = exec_pipeline(cur, env);
    char buffer[500];
    sprintf(buffer, "%d", ret);
    env = set_value(env, strdup("?"), strdup(buffer));
    cur = cur->next;
    while (cur)
    {
        if (cur->is_and && ret != 0)
            break;
        else if (!cur->is_and && ret == 0)
            break;
        ret = exec_pipeline(cur, env);
        sprintf(buffer, "%d", ret);
        env = set_value(env, strdup("?"), strdup(buffer));
        cur = cur->next;
    }
    return ret;
}

static int exec_pipe(struct env *env, struct command_node *command)
{
    int ret = -1;

    pid_t read_pid = fork();
    if (!read_pid)
    {
        int pipefd[2];
        pipe(pipefd);
        pid_t write_pid = fork();
        if (!write_pid)
        {
            if (command->next)
            {
                close(pipefd[0]);
                close(1);
                dup(pipefd[1]);
                close(pipefd[1]);
                ret = exec_command(command, env);
            }
            exit(ret);
        }
        int wstatus;

        int wret_read = waitpid(read_pid, &wstatus, 0);
        ret = wret_read > 0 ? WEXITSTATUS(wstatus) : 0;
        if (command->next)
        {
            close(0);
            dup(pipefd[0]);
            close(pipefd[1]);
            ret = exec_pipe(env, command->next);
        }
        else
            ret = exec_command(command, env);
        exit(ret);
    }

    int wstatus;

    int wret_read = waitpid(read_pid, &wstatus, 0);
    ret = wret_read > 0 ? WEXITSTATUS(wstatus) : 0;

    return ret;
}

int exec_pipeline(struct pipeline_node *pipeline, struct env *env)
{
    if (!pipeline->command)
        return pipeline->is_not ? 1 : 0;

    int ret;
    if (pipeline->command->next)
        ret = exec_pipe(env, pipeline->command);
    else
        ret = exec_command(pipeline->command, env);

    return pipeline->is_not ? !ret : ret;
}
