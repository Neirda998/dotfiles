#include <stdlib.h>
#include <string.h>

#include "input/env.h"
#include "utils/memory.h"

struct aliases *new_aliases(void)
{
    struct aliases *aliases = xcalloc(1, sizeof(struct aliases));

    aliases->capacity = 8;
    aliases->size = 0;
    aliases->data = xcalloc(8, sizeof(struct alias *));

    return aliases;
}

struct alias *new_alias(char *name, char *substitution)
{
    struct alias *alias = xcalloc(1, sizeof(*alias));

    alias->name = name ? strdup(name) : NULL;
    alias->substitution = substitution ? strdup(substitution) : NULL;

    return alias;
}

void aliases_resize(struct aliases *aliases)
{
    struct alias **temp = xcalloc(aliases->capacity * 2, sizeof(struct alias *));

    for (int i = 0; i < aliases->size; i++)
        temp[i] = aliases->data[i];
    free(aliases->data);
    aliases->data = temp;
    aliases->capacity *= 2;
}

void aliases_insert(struct aliases *aliases, struct alias *alias)
{
    if (aliases->size == aliases->capacity)
        aliases_resize(aliases);
    int idx = 0;
    while (aliases->data[idx]
            && strcmp(alias->name, aliases->data[idx]->name) > 0)
        idx++;
    for (int i = aliases->size - 1; i >= idx; i--)
        aliases->data[i + 1] = aliases->data[i];
    aliases->data[idx] = alias;
    aliases->size++;
}

void aliases_delete(struct aliases *aliases, int idx)
{
    if (idx < 0 || idx >= aliases->size)
        return;
    free(aliases->data[idx]->name);
    free(aliases->data[idx]->substitution);
    free(aliases->data[idx]);
    for (int i = idx + 1; i < aliases->size; i++)
        aliases->data[i - 1] = aliases->data[i];
    aliases->size--;
}
