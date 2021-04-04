/**
** \file
** Utility scripts for ast printing.
*/
#ifndef AST_UTILS_H
# define AST_UTILS_H

#include <stdio.h>

/**
** The ast printer structure.
** Contains:
** The dot file stream,
** The current key to be added to the tree.
*/
struct ast_printer
{
    FILE *dot;
    int key;
};

/**
** Adds a node to the dot file.
** @param ast The ast printer struct.
** @param name The label of the node.
*/
void ast_printer_add_node(struct ast_printer *ast, char *name);

/**
** Adds an edge between current ast key and another key giuven in parameter.
** @param ast The ast printer struct.
** @param src The source node of the edge.
*/
void ast_printer_add_edge(struct ast_printer *ast, int src);

/**
** Ends the process of creatng the dot file.
** @param ast The ast printer struct.
*/
void ast_printer_end(struct ast_printer *ast);

#endif /* ! AST_UTILS_H */
