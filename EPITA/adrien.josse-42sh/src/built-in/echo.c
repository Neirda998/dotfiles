#include <err.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include "built-in/echo.h"

#include "utils/memory.h"

static int *get_echo_opt_value(char *str)
{
    int *res = xcalloc(2, sizeof(int));
    if (*str != '-')
        return res;

    for (int idx = 0; str[idx]; ++idx)
    {
        if (str[idx] == 'e')
            res[0] = 1;
        else if (str[idx] == 'E')
            res[0] = -1;
        else if (str[idx] == 'n')
            res[1] = 1;
    }

    return res;
}

static struct echo_options *echo_opt(int ac, char **av)
{
    struct echo_options *opt = xcalloc(1, sizeof(struct echo_options));

    int idx = 1;
    int found = 0;
    int *vals = NULL;
    while (!found && idx < ac)
    {
        if (av[idx][0] != '-' || !av[idx][1] ||
                (av[idx][1] != 'e' && av[idx][1] != 'n' && av[idx][1] != 'E'))
            found = 1;
        else
        {
            vals = get_echo_opt_value(av[idx]);
            opt->e = vals[0];
            opt->n = vals[1];
            idx++;
        }
    }
    opt->index = idx;
    free(vals);
    return opt;
}

static void lm_sputchar(char *str, int *idx, char c)
{
    if (!str)
        return;
    sprintf(str + *idx, "%c", c);
    *idx = *idx + 1;
}

static void print_backslash(char *str, int *idx, char *line, int *ptr)
{
    char c = line[*ptr];
    if (c == 'a')
        lm_sputchar(str, idx, '\a');
    else if (c == 'b')
        lm_sputchar(str, idx, '\b');
    else if (c == 'f')
        lm_sputchar(str, idx, '\f');
    else if (c == 'n')
        lm_sputchar(str, idx, '\n');
    else if (c == 'r')
        lm_sputchar(str, idx, '\r');
    else if (c == 't')
        lm_sputchar(str, idx, '\t');
    else if (c == 'v')
        lm_sputchar(str, idx, '\v');
    else if (c == '\\')
        lm_sputchar(str, idx, '\\');
    *ptr = *ptr + 1;
}

int is_quoted(char *str)
{
    int ln = strlen(str);
    return str[0] == '\"' && str[ln - 1] == '\"';
}

void echo_arg(char *line, struct echo_options *opt)
{
    int idx = 0;
    int ptr = 0;
    char display[4096];
    char *pointer = display;
    int is_q = is_quoted(line);

    if (is_q)
    {
        ptr++;
        line[strlen(line) - 1] = '\0';
    }

    while (line[ptr] != '\0')
    {
        if (opt->e == 1 && is_q && line[ptr] == '\\')
        {
            ptr++;
            print_backslash(pointer, &idx, line, &ptr);
        }
        else if (line[ptr] == '\\')
        {
            if (!is_q)
                ptr++;
            lm_sputchar(pointer, &idx, line[ptr]);
            ptr++;
        }
        else
        {
            lm_sputchar(pointer, &idx, line[ptr]);
            ptr++;
        }
    }
    printf("%s", display);
}

int builtin_echo(int ac, char **av)
{
    struct echo_options *opt = echo_opt(ac, av);
    if (!opt)
        return 1;
    for (int i = opt->index; i < ac; i++)
    {
        echo_arg(av[i], opt);
        if (i != ac - 1)
            printf(" ");
    }
    if (!opt->n)
        printf("\n");
    free(opt);
    fflush(stdout);
    return 0;
}
