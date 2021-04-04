#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils/fd_utils.h"
#include "utils/memory.h"

#include "parser/redirection.h"

#include "exec/exec_redirection.h"

int exec_redirection_dgreat(struct redirection_node *redir, struct env *env)
{
    int new_fd = redir->ionumber == -1 ? 1 : redir->ionumber;
    int old_fd = open(redir->redirect_out,
                      O_WRONLY | O_CREAT | O_APPEND, 0755);
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

int exec_redirection_clobber(struct redirection_node *redir, struct env *env)
{
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
        close(backup_fd);
        fd_backup_pop(env->table);
        warnx("bad file descriptor");
        return 1;
    }
    return 0;
}

int exec_redirection_lessgreat(struct redirection_node *redir, struct env *env)
{
    int new_fd = redir->ionumber == -1 ? 0 : redir->ionumber;
    int old_fd = open(redir->redirect_out,
                      O_RDWR | O_CREAT, 0755);
    if (old_fd == -1)
    {
        warnx("%s: no such file or directory", redir->redirect_out);
        return 1;
    }
    int backup_fd = dup(new_fd);
    env->table = fd_backup_push(env->table, old_fd, new_fd, backup_fd);
    if (dup2(old_fd, new_fd) == -1 && errno == EBADF)
    {
        close(backup_fd);
        fd_backup_pop(env->table);
        warnx("bad file descriptor");
        return 1;
    }
    return 0;
}

int exec_redirection_dless(struct redirection_node *redir, struct env *env)
{
    int new_fd = redir->ionumber == -1 ? 0 : redir->ionumber;
    int old_fd = open("/tmp", O_TMPFILE | O_RDWR, 0666);
    if (old_fd == -1)
    {
        warnx("could not open here doc");
        return 1;
    }

    FILE *tmp = fdopen(old_fd, "r+");
    if (redir->redirect_out)
        write_heredoc(redir, tmp, 0);

    int backup_fd = dup(new_fd);
    env->table = fd_backup_push(env->table, old_fd, new_fd, backup_fd);
    if (dup2(old_fd, new_fd) == -1 && errno == EBADF)
    {
        fd_backup_pop(env->table);
        warnx("bad file descriptor");
        return 1;
    }

    fclose(tmp);
    return 0;
}

int exec_redirection_dlessdash(struct redirection_node *redir, struct env *env)
{
    int new_fd = redir->ionumber == -1 ? 0 : redir->ionumber;
    if (!redir->redirect_out)
        return 0;
    int old_fd = open("/tmp", O_TMPFILE | O_RDWR, 0666);
    if (old_fd == -1)
    {
        warnx("could not open here doc");
        return 1;
    }

    FILE *tmp = fdopen(old_fd, "r+");
    if (redir->redirect_out)
        write_heredoc(redir, tmp, 1);

    int backup_fd = dup(new_fd);
    env->table = fd_backup_push(env->table, old_fd, new_fd, backup_fd);
    if (dup2(old_fd, new_fd) == -1 && errno == EBADF)
    {
        fd_backup_pop(env->table);
        warnx("bad file descriptor");
        return 1;
    }

    fclose(tmp);
    return 0;
}
