#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <err.h>

#include "input/input.h"

FILE *open_input(int flag_c, char *in_str)
{
    FILE *instream;
    if (flag_c)
        instream = fmemopen(in_str, strlen(in_str) + 1, "r");
    else
        instream = fopen(in_str, "r");
    if (!instream)
        errx(127, "%s: no such file or directory", in_str);
    return instream;
}

void close_input(FILE *instream)
{
    fclose(instream);
}
