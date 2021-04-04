#include <err.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input/option.h"

static int shopt_to_index(char *shopt)
{
    if (!shopt)
        errx(2, "Missing argument for [-+]O");
    if (strcmp("ast_print", shopt) == 0)
        return 0;
    if (strcmp("dotglob", shopt) == 0)
        return 1;
    if (strcmp("expand_aliases", shopt) == 0)
        return 2;
    if (strcmp("extglob", shopt) == 0)
        return 3;
    if (strcmp("nocaseglob", shopt) == 0)
        return 4;
    if (strcmp("nullglob", shopt) == 0)
        return 5;
    if (strcmp("sourcepath", shopt) == 0)
        return 6;
    if (strcmp("xpg_echo", shopt) == 0)
        return 7;
    return -1;
}

static void o_parsing(struct opt **opt, int ac, char **av)
{
    struct opt *temp = *opt;
    int shopt_ind = 0;
    for (int i = 1; i < ac; i++)
    {
        if (strcmp(av[i], "+O") == 0)
        {
            shopt_ind = shopt_to_index(av[i + 1]);
            if (shopt_ind == -1)
                errx(2, "invlid shell option name");
            else
                temp->shopt[shopt_ind] = -1;
            temp->index += 2;
        }
        else if (strcmp(av[i], "-O") == 0)
        {
            shopt_ind = shopt_to_index(av[i + 1]);
            if (shopt_ind == -1)
                errx(2, "invalid shell option name");
            else
                temp->shopt[shopt_ind] = 1;
            temp->index++;
        }
        else if (strcmp(av[i], "-o") == 0)
        {
            if (strcmp(av[i + 1], "noclobber") == 0)
                temp->is_noclobber = 1;
            temp->index++;
        }
        else if (strcmp(av[i], "+o") == 0)
        {
            if (strcmp(av[i + 1], "noclobber") == 0)
                temp->is_noclobber = -1;
            temp->index += 2;
        }
    }
    *opt = temp;
}

#ifdef _DEBUG
static void print_opt(struct opt *opt)
{
    printf("-c: %d %s\n", opt->is_c, opt->c_string);
    printf("--norc: %d\n", opt->is_norc);
    printf("--ast-print: %d\n", opt->is_ast_print);
    for (int i = 0; i < 8; i++)
        printf("shopt[%d]: %d\n", i, opt->shopt[i]);
}
#endif

void free_options(struct opt *opt)
{
    free(opt);
}

struct opt *parse_options(int ac, char **av)
{
    struct opt *opt = calloc(1, sizeof(struct opt));
    if (!opt)
        return NULL;
    static struct option long_opt[] = {
        {"norc", no_argument, 0, 0},
        {"ast-print", no_argument, 0, 0}
    };
    int c = 0;
    int opt_index = 0;
    o_parsing(&opt, ac, av);
    while (c != -1)
    {
        c = getopt_long(ac, av, ":c:Oo", long_opt, &opt_index);
        switch (c)
        {
        case 0:
            if (strcmp(long_opt[opt_index].name, "norc") == 0)
                opt->is_norc = 1;
            else if (strcmp(long_opt[opt_index].name, "ast-print") == 0)
                opt->is_ast_print = 1;
            break;
        case 'c':
            opt->is_c = 1;
            opt->c_string = optarg;
            break;
        case '?':
            errx(2, "Unknown option");
            break;
        case ':':
            errx(2, "Missing argument for -c");
            break;
        default:
            break;
        }
    }
    opt->index += optind;
    return opt;
}
