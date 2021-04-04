/**
** \file
** Utils functions of the fd_backup structure managment.
*/

#ifndef FD_UTILS_H
# define FD_UTILS_H

#include <stdio.h>

#include "input/env.h"

#include "parser/redirection.h"

/**
** Pops the last element of the fd_backup list.
** @param table The fd_backup list to pop.
*/
void fd_backup_pop(struct fd_backup *table);

/**
** Adds a new element in the fd_backup structure.
** @param table The fd_backup list where the push needs to be done.
** @param old_fd The old_fd to push.
** @param new_fd The new_fd to push.
** @param backup_fd The backup_fd to push.
** @return Returns the modified fd_backup list.
*/
struct fd_backup *fd_backup_push(struct fd_backup *table, int old_fd,
                                        int new_fd, int backup_fd);

/**
** Restore and free all the file descriptors in the fd_backup list.
** @param table The fd_backup list to restore.
** @return Returns NULL.
*/
struct fd_backup *restore_fd_table(struct fd_backup *table);

/**
** Writes a heredoc in a stream.
** @param redir The REDIRECTION NODE where the heredoc exits.
** @param stream The stream where the heredoc needs to be written.
** @param is_dashed A boolean true when a dash redirection operator is used.
*/
void write_heredoc(struct redirection_node *redir, FILE *stream,
                   int is_dashed);

#endif /* ! FD_UTILS_H */
