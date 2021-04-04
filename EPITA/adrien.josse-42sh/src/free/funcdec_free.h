/**
** \file
** Freeing function of the funcdec nodes.
*/
#ifndef FUNCDEC_FREE_H
# define FUNCDEC_FREE_H

#include "parser/funcdec.h"

/**
** Freeing of a FUNCDEC NODE.
** @param the FUNCDEC NODE to free.
*/
void funcdec_node_free(struct funcdec_node *funcdec);

#endif /* ! FUNCDEC_FREE_H */
