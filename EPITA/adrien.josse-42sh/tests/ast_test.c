#include <criterion/criterion.h>

#include "ast.h"
#include "token.h"

Test(ast, ast_init_and_free)
{
    struct ast *ast = ast_init(NULL);

    cr_expect_not_null(ast);
    cr_expect_null(ast->token);
    cr_expect_null(ast->left);
    cr_expect_null(ast->right);

    ast_free(ast);
}

Test(ast, NAME_root)
{
    struct ast *ast = ast_init(token_create("foo", NAME));

    cr_expect_not_null(ast);
    cr_expect_not_null(ast->token);
    cr_expect_null(ast->left);
    cr_expect_null(ast->right);

    ast_free(ast);
}
