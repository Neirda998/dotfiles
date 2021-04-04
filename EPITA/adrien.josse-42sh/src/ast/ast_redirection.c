
#include "ast/ast_redirection.h"

#include "ast/ast_utils.h"

#include "lexer/token.h"
#include "parser/redirection.h"

void ast_redirection(struct redirection_node *redir,
                     struct ast_printer *ast)
{
    char *op = "";
    if (redir->op == LESS)              /*  <  */
        op = "\\<";
    else if (redir->op == GREAT)        /*  >  */
        op = "\\>";
    else if (redir->op == LESSAND)      /* <&  */
        op = "\\<\\&";
    else if (redir->op == GREATAND)     /* >&  */
        op = "\\>\\&";
    else if (redir->op == DLESS)        /* <<  */
        op = "\\<\\<";
    else if (redir->op == DGREAT)       /* >>  */
        op = "\\>\\>";
    else if (redir->op == DLESSDASH)    /* <<- */
        op = "\\<\\<\\-";
    else if (redir->op == CLOBBER)      /*  >| */
        op = "\\>\\|";
    else // redir->op == LESSGREAT)     /*  <> */
        op = "\\<\\>";

    fprintf(ast->dot, "\t%d [shape=Mrecord label=\"{redirection|%d%s%s}\"]\n",
        ast->key++,
        redir->ionumber,
        op,
        redir->redirect_out
    );

}
