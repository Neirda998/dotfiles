#include <err.h>
#include <stdlib.h>
#include <stdarg.h>

#include "utils/memory.h"

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
        errx(2, "memory exhausted !");
    return ptr;
}

void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    if (!ptr)
        errx(2, "memory exhausted !");
    return ptr;
}

void *xrealloc(void *ptr, size_t size)
{
    void *tmp = realloc(ptr, size);
    if (!tmp)
        errx(2, "memory exhausted !");
    ptr = tmp;
    return ptr;
}
