#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "exec/exec_redirection.h"

#include "utils/fd_utils.h"
#include "utils/memory.h"

#include "parser/redirection.h"

#include "expand/expand.h"

static char *remove_backslashes(char *word)
{
    int r_idx = 0;
    int w_idx = 0;
    while (word[r_idx])
    {
        if (word[r_idx] != '\\'
            || (!word[r_idx + 1] || word[r_idx + 1] == '\\'))
                word[w_idx++] = word[r_idx];
        r_idx++;
    }
    word[w_idx] = '\0';
    word = xrealloc(word, w_idx + 1);
    return word;
}

int exec_redirection(struct redirection_node *redir, struct env *env)
{
    if (redir->expand)
    {
        redir->redirect_out = expand_vars(redir->redirect_out, env, 0);
        redir->redirect_out = remove_backslashes(redir->redirect_out);
    }

    if (redir->op == LESS)              /*  <  */
        return exec_redirection_less(redir, env);
    else if (redir->op == GREAT)        /*  >  */
        return exec_redirection_great(redir, env);
    else if (redir->op == LESSAND)      /* <&  */
        return exec_redirection_lessand(redir, env);
    else if (redir->op == GREATAND)     /* >&  */
        return exec_redirection_greatand(redir, env);
    else if (redir->op == DLESS)        /* <<  */
        return exec_redirection_dless(redir, env);
    else if (redir->op == DGREAT)       /* >>  */
        return exec_redirection_dgreat(redir, env);
    else if (redir->op == DLESSDASH)    /* <<- */
        return exec_redirection_dlessdash(redir, env);
    else if (redir->op == CLOBBER)      /*  >| */
        return exec_redirection_clobber(redir, env);
    else // redir->op == LESSGREAT)     /*  <> */
        return exec_redirection_lessgreat(redir, env);
    return 1;
}

static int is_numbers(char *str)
{
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int exec_redirection_less(struct redirection_node *redir, struct env *env)
{
    int new_fd = redir->ionumber == -1 ? 0 : redir->ionumber;
    int old_fd = open(redir->redirect_out, O_RDONLY);
    if (old_fd == -1)
    {
        warnx("%s: no such file or directory", redir->redirect_out);
        return 1;
    }
    int backup_fd = dup(new_fd);
    env->table = fd_backup_push(env->table, old_fd, new_fd, backup_fd);
    if (dup2(old_fd, new_fd) == -1 && errno == EBADF)
    {
        fd_backup_pop(env->table);
        warnx("bad file descriptor");
        return 1;
    }
    return 0;
}

int exec_redirection_great(struct redirection_node *redir, struct env *env)
{
    if (env->opts->is_noclobber == 1 &&
            access(redir->redirect_out, F_OK) != -1)
    {
        warnx("cannot overwrite existing file");
        return 1;
    }
    int new_fd = redir->ionumber == -1 ? 1 : redir->ionumber;
    int old_fd = open(redir->redirect_out,
                      O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (old_fd == -1)
    {
        warnx("%s: no such file or directory", redir->redirect_out);
        return 1;
    }
    int backup_fd = dup(new_fd);
    env->table = fd_backup_push(env->table, old_fd, new_fd, backup_fd);
    if (dup2(old_fd, new_fd) == -1 && errno == EBADF)
    {
        fd_backup_pop(env->table);
        warnx("bad file descriptor");
        return 1;
    }
    return 0;
}

int exec_redirection_lessand(struct redirection_node *redir, struct env *env)
{
    int new_fd = redir->ionumber == -1 ? 0 : redir->ionumber;
    int old_fd = strcmp(redir->redirect_out, "-") == 0 ?
        -1 : atoi(redir->redirect_out);
    if (old_fd != -1 && !is_numbers(redir->redirect_out))
    {
        warnx("%s: ambiguous redirect", redir->redirect_out);
        return 1;
    }
    if (old_fd == new_fd || old_fd == 0)
        return 0;
    int backup_fd = dup(new_fd);
    env->table = fd_backup_push(env->table, old_fd, new_fd, backup_fd);
    if (old_fd == -1)
    {
        close(new_fd);
        return 0;
    }
    if (dup2(old_fd, new_fd) == -1 && errno == EBADF)
    {
        fd_backup_pop(env->table);
        warnx("bad file descriptor");
        return 1;
    }
    return 0;
}

int exec_redirection_greatand(struct redirection_node *redir, struct env *env)
{
    int new_fd = redir->ionumber == -1 ? 1 : redir->ionumber;
    int old_fd = strcmp(redir->redirect_out, "-") == 0 ?
        -1 : atoi(redir->redirect_out);
    if (old_fd != -1 && !is_numbers(redir->redirect_out))
    {
        old_fd = open(redir->redirect_out,
                    O_WRONLY | O_CREAT | O_TRUNC, 0755);
    }
    if (old_fd == new_fd || old_fd == 0)
        return 0;
    int backup_fd = dup(new_fd);
    env->table = fd_backup_push(env->table, old_fd, new_fd, backup_fd);
    if (old_fd == -1)
    {
        close(new_fd);
        return 0;
    }
    if (dup2(old_fd, new_fd) == -1 && errno == EBADF)
    {
        fd_backup_pop(env->table);
        warnx("bad file descriptor");
        return 1;
    }
    return 0;
}
