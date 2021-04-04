#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "memory.h"
#include "xstring.h"

char *xstrcat(char *s1, char *s2)
{
    if (!s1 && !s2)
        return strdup("");
    if (!s1)
    {
        char *temp = strdup(s2);
        free(s2);
        return temp;
    }
    else if (!s2)
    {
        char *temp = strdup(s1);
        free(s1);
        return temp;
    }
    size_t len_s1 = strlen(s1);
    size_t len_s2 = strlen(s2);
    char *res = xmalloc(len_s1 + len_s2 + 1);
    for (size_t i = 0; i < len_s1; i++)
        res[i] = s1[i];
    for (size_t i = 0; i < len_s2; i++)
        res[i + len_s1] = s2[i];
    res[len_s1 + len_s2] = '\0';
    free(s1);
    free(s2);
    return res;
}

char *xstrcatchar(char *s, char c)
{
    int size = strlen(s);
    s = xrealloc(s, size + 2);
    s[size] = c;
    s[size + 1] = '\0';
    return s;
}

int is_number(const char *str)
{
    int idx = 0;
    while (str[idx])
    {
        if (!isdigit(str[idx]))
            return 0;
        idx++;
    }
    return 1;
}
