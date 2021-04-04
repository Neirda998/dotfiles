#include <err.h>
#include <stdlib.h>

#include "utils/xstring.h"

#include "built-in/exit.h"

int builtin_exit(int ac, char **av)
{
    if (ac > 2)
    {
        warnx("exit: too many arguments");
        return 1;
    }
    if (ac == 1)
        exit(0);
    unsigned char code = 0;
    if (is_number(av[1]))
        code = atoi(av[1]);
    else
    {
        warnx("exit : %s: numeric argument required", av[1]);
        exit(2);
    }
    int ret = code;
    exit(ret);
    return ret;
}
