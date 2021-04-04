#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "built-in/cd.h"

int cd_single(char *str)
{
    int check = 0;
    if (!str)
        return 1;
    check = chdir(str);
    if (check != 0)
    {
        if (errno == ENOTDIR)
            warnx("cd: %s: Not a directory", str);
        else if (errno == ENOENT)
            warnx("cd: %s: No such file or directory", str);
        return 1;
    }
    return 0;
}

int builtin_cd(int ac, char **av)
{
    char pwd[4096];
    char *ptr = getcwd(pwd, 4096);
    char *home_path = getenv("HOME");
    char *prev_path = getenv("OLDPWD");
    if (ac > 2)
    {
        warnx("cd: too many arguments");
        return 1;
    }
    if (ac == 1)
        return cd_single(home_path);
    if (strcmp(av[1], "~") == 0)
        return cd_single(home_path);
    if (strcmp(av[1], "-") == 0)
    {
        if (!prev_path)
        {
            warnx("cd: OLDPWD not set");
            return 1;
        }
        else
        {
            int ret = cd_single(prev_path);
            ptr = getcwd(pwd, 4096);
            printf("%s\n", ptr);
            fflush(NULL);
            setenv("OLDPWD", ptr, 1);
            return ret;
        }
    }
    setenv("OLDPWD", ptr, 1);
    return cd_single(av[1]);
}
