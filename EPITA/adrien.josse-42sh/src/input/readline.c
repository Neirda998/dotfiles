#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

#include "utils/memory.h"

#include "input/readline.h"

#include "history/history.h"
/**
** Checks if current readline stream is a terminal.
** @return Returns 1 if the stream is interactive, returns 0 otherwise.
*/
static int is_interactive(void)
{
    int tty = rl_instream ? fileno(rl_instream) : fileno(stdin);

    return isatty(tty);
}

/**
** Modify the terminal settings for readline's use.
** @param meta_flag This flag should be zero
** if readline should read 1 bit inputs (characters).
*/
static void prep_terminal(int meta_flag)
{
    if (is_interactive())
        rl_prep_terminal(meta_flag);
}

/**
** A basic signal handler for SIGINT (Ctrl+C).
** @param signo The caught signal's number.
*/
void handle_signals(int status)
{
    status = 0;
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", status); // Clear the previous text
    rl_redisplay();
}

void setup_signal(void)
{
    if (signal(SIGINT, handle_signals) == SIG_ERR)
        errx(3, "Failed to catch SIGINT signal");
}

/**
** Adds a '\n' at end of readline.
*/
static char *line_jump(char *str)
{
    if (!str)
        return NULL;
    size_t ln = strlen(str);
    str = xrealloc(str, sizeof(char) * (ln + 2));
    str[ln] = '\n';
    str[ln + 1] = '\0';
    return str;
}

char *get_next_line(const char *PS1, const char *PS2, int is_open)
{
    char *ret = NULL;
    size_t n = 0;
    rl_prep_term_function = prep_terminal;

    const char *prompt = is_open ? PS2 : PS1;

    if (!is_interactive())
    {
        int err;
        if (!rl_instream)
            err = getline(&ret, &n, stdin);
        else
            err = getline(&ret, &n, rl_instream);
        if (err == -1)
        {
            free(ret);
            return NULL;
        }
    }
    else
    {
        ret = readline(prompt);
        if (!ret)
        {
            printf("exit\n");
            save_history();
            exit(0);
        }
        ret = line_jump(ret);
    }
    return ret;
}
