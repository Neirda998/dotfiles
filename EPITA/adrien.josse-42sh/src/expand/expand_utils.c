#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "expand/expand_utils.h"

#include "utils/memory.h"

#include "expand/variables.h"

char *expand_in_str(char *str, char *replaced, char *replacement)
{
    int str_len = strlen(str);
    int replaced_len = strlen(replaced);
    int replacement_len = strlen(replacement);
    int res_len = str_len + replacement_len - replaced_len;
    char *res = xmalloc(res_len + 1);
    int i = 0;
    int j = 0;
    int found = 0;
    while (i < str_len)
    {
        if (!found && strncmp(str + i, replaced, replaced_len) == 0)
        {
            sprintf(res + j, "%s", replacement);
            i += replaced_len;
            j += replacement_len;
            found = 1;
        }
        else
        {
            res[j] = str[i];
            i++;
            j++;
        }
    }
    res[res_len] = '\0';
    free(str);
    return res;
}

char *get_ifs(struct env *env)
{
    char *ifs;
    char *tmp_ifs = get_value(env, "IFS");
    if (*tmp_ifs)
        ifs = strdup(tmp_ifs);
    else
        ifs = strdup(" \t\n");
    return ifs;
}
