#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

#include "history.h"

void write_line_history(char *real)
{
    if (!real)
        return;
    char *line = strdup(real);
    int len = strlen(line);
    if (len > 0)
    {
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        add_history(line);
    }
    free(line);
}

void load_history(void)
{
    using_history();
    clear_history();
    char name[4096];
    sprintf(name, "%s/.42sh_history", getenv("HOME"));
    FILE *hist = fopen(name, "r");
    if (!hist)
        return;
    int check = 0;
    size_t len = 0;
    char *line = NULL;
    while (check != -1)
    {
        check = getline(&line, &len, hist);
        if (check != -1)
        {
            for (int i = 0; line[i] != '\0'; i++)
            {
                if (line[i] == '\n')
                    line[i] = '\0';
            }
            if (strlen(line) > 0)
                add_history(line);
        }
    }
    free(line);
}

void display_history(void)
{
    HISTORY_STATE *state = history_get_history_state();
    if (!state)
        return;
    for (int i = 0; i < state->length; i++)
        printf("%*d  %s\n", 5, i, state->entries[i]->line);
    free(state);
}

int builtin_history(int ac, char **av)
{
    int check = 0;
    if (ac == 1)
    {
        display_history();
        return 0;
    }
    while (check != -1)
    {
        check = getopt(ac, av, "rc");
        if (check == '?')
        {
            warnx("Unknown option");
            return 1;
        }
        else if (check == 'r')
            load_history();
        else if (check == 'c')
            clear_history();
    }
    return 0;
}

void save_history(void)
{
    char name[4096];
    sprintf(name, "%s/.42sh_history", getenv("HOME"));
    FILE *hist = fopen(name, "w+");
    if (!hist)
        return;
    HISTORY_STATE *state = history_get_history_state();
    if (!state)
        return;
    for (int i = 0; i < state->length; i++)
        fprintf(hist, "%s\n", state->entries[i]->line);
    free(state);
    fclose(hist);
}
