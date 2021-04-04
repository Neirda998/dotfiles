#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <err.h>
#include <readline/readline.h>

#include "utils/xstring.h"

#include "input/input.h"

#include "expand/expand_command.h"

#include "expand/variables.h"
#include "expand/expand_utils.h"

#include "exec/main_utils.h"

#define BUFFER_SIZE 8192

static char *expand_command(char *word, struct env *env)
{
    char buffer[BUFFER_SIZE + 1];
    char *ret = strdup("");
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        warnx("Cannot execute subshell");
        return strdup("");
    }
    pid_t pid = fork();

    if (!pid)
    {
        // Child
        close(pipe_fd[0]);
        close(1);
        dup(pipe_fd[1]);
        close(pipe_fd[1]);
        rl_instream = open_input(1, word);
        run_in_stream(env);
        exit(0);
    }
    else
    {
        // Parent
        close(pipe_fd[1]);
        while (1)
        {
            int read_ret = read(pipe_fd[0], buffer, BUFFER_SIZE);
            if (read_ret == -1)
            {
                warnx("Cannot execute subshell");
                return ret;
            }
            if (!read_ret)
                return ret;
            buffer[read_ret] = '\0';
            ret = xstrcat(ret, strdup(buffer));
        }
        close(pipe_fd[0]);
        return ret;
    }
}

char *expand_commands(char *word, struct env *env)
{
    char quote = 0;
    if(!word)
        return NULL;
    int idx = 0;
    while (word[idx])
    {
        if (quote != '\'' && (word[idx] == '`' || (word[idx] == '$'
                                                   && word[idx + 1] == '('
                                                   && word[idx + 2] != '(')))
        {
            int len = 0;
            int is_para = word[idx + 1] == '(';
            char *full_expansion;
            char *to_expand;
            if (is_para)
            {
                while (word[idx + len + 2] != ')')
                    len++;
                full_expansion = strndup(word + idx, len + 3);
                to_expand = strndup(word + idx + 2, len);
            }
            else
            {
                while (word[idx + len + 1] != '`')
                    len++;
                full_expansion = strndup(word + idx, len + 2);
                to_expand = strndup(word + idx + 1, len);
            }
            char *expand_val = expand_command(to_expand, env);
            char *res = expand_in_str(word, full_expansion, expand_val);
            free(to_expand);
            idx += strlen(expand_val);
            free(full_expansion);
            free(expand_val);
            word = res;
        }
        else
        {
            if (word[idx] == '\'' || word[idx] == '"')
            {
                if (!quote)
                    quote = word[idx];
                else if (quote == word[idx])
                    quote = 0;
            }
            idx++;
        }
    }
    return word;
}
