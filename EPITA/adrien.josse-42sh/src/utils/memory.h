/**
** \file
** \brief smart allocations.
**
** This file contains a set of allocation functions that handle errors.
*/

#pragma once

#include <stddef.h>

/**
** A malloc with error handling.
** This functions exit with error code 2 if malloc fails.
** @param size The size in bytes of the needed memory space.
** @return Returns a valid pointer to a memory space of size bytes.
*/
void *xmalloc(size_t size);

/**
** A calloc with error handling.
** This functions exit with error code 2 if calloc fails.
** @param nmemb The max number of members in the memory space.
** @param size The size in bytes of each member.
** @return Returns a valid pointer to a memory space able to
** contain nmemb members of size bytes.
*/
void *xcalloc(size_t nmemb, size_t size);

/**
** A realloc with error handling.
** This functions exit with error code 2 if realloc fails.
** @param ptr The pointer to be re-allocated
** @param size The size in bytes of the needed memory space.
** @return Returns a ptr reallocated to a memory space of size bytes.
*/
void *xrealloc(void *ptr, size_t size);
