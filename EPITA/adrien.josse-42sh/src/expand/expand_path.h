/**
** \file
** Header for path expansion.
*/

#ifndef EXPAND_PATH_H
# define EXPAND_PATH_H

/**
** Path list structure.
** Representation of a list of file names.
*/
struct pathlist
{
    int size;     ///< the size of the list.
    int capacity; ///< the capacity of the list.
    char **data;  ///< the list of file names.
    char *path;   ///< the path to the file.
};

/**
** Path expansion function.
** @param match The word to match.
** @return Returns the expanded path.
*/
char *expand_path(char *match);

#endif /* ! EXPAND_PATH_H */
