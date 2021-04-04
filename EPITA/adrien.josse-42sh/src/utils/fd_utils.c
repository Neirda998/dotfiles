#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#include "utils/fd_utils.h"

#include "parser/redirection.h"

#include "utils/memory.h"

struct fd_backup *fd_backup_push(struct fd_backup *table, int old_fd,
                                        int new_fd, int backup_fd)
{
    struct fd_backup *elem = xcalloc(1, sizeof(*elem));
    elem->new_fd = new_fd;
    elem->old_fd = old_fd;
    elem->backup_fd = backup_fd;
    if (!table)
        return elem;
    struct fd_backup *ptr = table;
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = elem;
    return table;
}

void fd_backup_pop(struct fd_backup *table)
{
    struct fd_backup *ptr = table;
    if (!ptr || !ptr->next)
        return;
    while (ptr->next->next)
        ptr = ptr->next;
    close(ptr->next->backup_fd);
    free(ptr->next);
    ptr->next = NULL;
}

struct fd_backup *restore_fd_table(struct fd_backup *table)
{
    if (!table)
        return NULL;
    struct fd_backup *tmp = table;
    table = table->next;
    free(tmp);
    tmp = table;
    while (table)
    {
        table = table->next;
        dup2(tmp->backup_fd, tmp->new_fd);
        close(tmp->old_fd);
        close(tmp->backup_fd);
        free(tmp);
        tmp = table;
    }
    free(table);
    return NULL;
}

void write_heredoc(struct redirection_node *redir, FILE *stream,
                   int is_dashed)
{
    char *heredoc = redir->redirect_out;
    if (is_dashed)
        while (*heredoc == '\t')
            heredoc++;
    while (*heredoc)
    {
        if (is_dashed && *heredoc == '\n')
        {
            fputc(*heredoc, stream);
            heredoc++;

            while (*heredoc == '\t')
                heredoc++;
        }
        if (!*heredoc)
            break;
        fputc(*heredoc, stream);
        heredoc++;
    }
    fflush(stream);
    rewind(stream);
}
