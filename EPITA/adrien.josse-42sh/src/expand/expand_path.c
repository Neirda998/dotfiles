#include <dirent.h>
#include <err.h>
#include <fnmatch.h>
#include <libgen.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH_MAX_SIZE 4096

#include "expand/expand_path.h"

#include "utils/memory.h"
#include "utils/xstring.h"

#define MAX_PATH_SIZE 4096

static void pathlist_resize(struct pathlist *p_list)
{
    char **temp = xcalloc(p_list->capacity * 2, sizeof(char *));

    for (int i = 0; i < p_list->size; i++)
        temp[i] = p_list->data[i];
    free(p_list->data);
    p_list->data = temp;
    p_list->capacity *= 2;
}

static void free_pathlist(struct pathlist *p_list)
{
    if (!p_list)
        return;
    for (int i = 0; i < p_list->size; i++)
        free(p_list->data[i]);
    free(p_list->data);
    free(p_list->path);
    free(p_list);
}

static void pathlist_insert(struct pathlist *p_list, char *filename, int base)
{
    if (p_list->size == p_list->capacity)
        pathlist_resize(p_list);
    int idx = 0;
    filename = base ? basename(filename) : filename;
    setlocale(LC_ALL, "");
    while (p_list->data[idx]
            && strcoll(filename, p_list->data[idx]) > 0)
        idx++;
    for (int i = p_list->size - 1; i >= idx; i--)
        p_list->data[i + 1] = p_list->data[i];
    p_list->data[idx] = strdup(filename);
    p_list->size++;
}

static struct pathlist *pathlist_build(char *path)
{
    if (!path)
    {
        warnx("No path found");
        return NULL;
    }

    struct pathlist *p_list = xcalloc(1, sizeof(struct pathlist));
    p_list->data = xcalloc(8, sizeof(char *));
    p_list->capacity = 8;
    p_list->size = 0;
    p_list->path = strdup(path);

    DIR *dir = opendir(path);
    if (!dir)
    {
        free_pathlist(p_list);
        return NULL;
    }
    struct dirent *file = readdir(dir);
    while (file)
    {
        pathlist_insert(p_list, file->d_name, 1);
        file = readdir(dir);
    }
    closedir(dir);
    return p_list;
}

static char *next_component(char *str, int *idx)
{
    char *word = NULL;
    int len = 0;
    while (str[*idx] == '/')
        *idx = *idx + 1;
    if (str[*idx] == '\0')
        return NULL;
    while (str[*idx + len] && str[*idx + len] != '/')
        len++;
    word = strndup(str + *idx, len);
    return word;
}

static char *begin_expand(char *str, char *prev, char *next, int idx)
{
    int p_len = strlen(prev);
    int n_len = strlen(next);
    int s_len = strlen(str);
    char *res = xcalloc(s_len - p_len + n_len + 1, sizeof(char));

    for (int i = 0; i < idx; i++)
        res[i] = str[i];
    int i = idx;
    while (i - idx < n_len)
    {
        res[i] = next[i - idx];
        i++;
    }
    int j = idx + p_len;
    while (j < s_len)
    {
        res[i] = str[j];
        i++;
        j++;
    }
    return res;
}

static int is_dir(char *path)
{
    struct stat p_stat;
    if (stat(path, &p_stat) == -1)
        return 0;
    return S_ISDIR(p_stat.st_mode);
}

static void path_match(char *path, char *match, int idx, struct pathlist *found)
{
    char new_path[PATH_MAX_SIZE];
    char *comp = next_component(match, &idx);
    if (!comp)
        return;
    int save_idx = idx + strlen(comp);
    char *last = next_component(match, &save_idx);
    struct pathlist *p_list = pathlist_build(path);
    for (int i = 0; i < p_list->size; i++)
    {
        sprintf(new_path, "%s%s/", path, p_list->data[i]);
        char *recursive_path = strdup(new_path);
        if (fnmatch(comp, p_list->data[i], FNM_PATHNAME) == 0
            && (p_list->data[i][0] != '.' || *comp == '.'))
        {
            char *new_match = begin_expand(match, comp, p_list->data[i], idx);
            int len = strlen(p_list->data[i]);
            if (!last)
                pathlist_insert(found, new_match, 0);
            else if (is_dir(recursive_path) &&
                (strcmp(p_list->data[i], ".") || !strcmp(p_list->data[i] ,".")))
            {
                if (strcmp(p_list->data[i], "..") != 0
                    || strcmp(comp, "..") == 0)
                    path_match(recursive_path, new_match, idx + len, found);
            }
            free(new_match);
        }
        free(recursive_path);
    }
    free(last);
    free_pathlist(p_list);
    free(comp);
}

char *expand_path(char *match)
{
    char *first_path = *match == '/' ? "/" : "./";
    struct pathlist *found = xcalloc(1, sizeof(struct pathlist));
    found->data = xcalloc(8, sizeof(char *));
    found->capacity = 8;
    path_match(first_path, match, 0, found);
    if (found->size == 0)
    {
        free_pathlist(found);
        return match;
    }
    char *res = NULL;
    for (int i = 0; i < found->size; i++)
    {
        char *cpy = strdup(found->data[i]);
        if (i != 0)
            res = xstrcat(res, strdup(" "));
        res = xstrcat(res, cpy);
    }
    free_pathlist(found);
    free(match);
    return res;
}
