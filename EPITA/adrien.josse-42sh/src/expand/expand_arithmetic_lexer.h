/**
** \file
** Header for expansion of arithmetic expression (lexer part).
*/

#ifndef EXPAND_ARITHMETIC_LEXER_H
# define EXPAND_ARITHMETIC_LEXER_H

/**
** Enum of all binary operators handled.
*/
enum arithmetic_b_op
{
    B_OP_NONE = 0,  // No binary operator
    PLUS,           // +
    MINUS,          // -
    EXP,            // **
    MULT,           // *
    DIV,            // /
    LOG_AND,        // &&
    LOG_OR,         // ||
    BIT_AND,        // &
    BIT_OR,         // |
    BIT_XOR         // ^
};

/**
** Enum of all unary operators handled.
*/
enum arithmetic_u_op
{
    U_OP_NONE = 0,  // No unary operator
    U_PLUS,         // +
    U_MINUS,        // -
    LOG_NOT,        // !
    BIT_NOT         // ~
};

/**
** Enum of all token types.
*/
enum arithmetic_type
{
    NUMBER = 0,
    B_OP,
    U_OP,
    L_PARENTHESIS,
    R_PARENTHESIS,
    END
};

/**
** Structure of arithmetic token.
** Contains:
** An arithmetic type (number, binary/unary operator, parenthesis...)
** An unary operator type.
** A binary operator type.
**/
struct a_token
{
    enum arithmetic_type type;
    enum arithmetic_u_op u_op;
    enum arithmetic_b_op b_op;
    char *value;
};

/**
** Structure of arithmetic lexer.
** Contains:
** The string to be lexed.
** The lexer's current index.
** The next token to be returned.
**/
struct a_lexer
{
    char *str;
    int idx;
    struct a_token *next_token;
};

/**
** Arithmetic lexer context initialisation function.
** @param str The string to lexer.
** @return Returns an allocated lexer containing the basic lexer context.
** This reads the first line of input.
*/
struct a_lexer *set_a_lexer(char *str);

/**
** Gets next arithmetic token without eating word on input.
** @param a_lexer Current arithmetic lexer context.
** @param unary Indicates if an unary operator is expected.
** @return Token corresponding to the next word on input.
*/
struct a_token *a_peek(struct a_lexer *a_lexer, int unary);

/**
** Gets next arithmetic token and eats next word on input.
** @param a_lexer Current arithmetic lexer context.
** @param unary Indicates a pop unary case.
** @return Token corresponding to the next word on input.
*/
struct a_token *a_pop(struct a_lexer *a_lexer, int unary);

/**
** Arithmetic token de-allocation function.
** @param Token to be freed.
*/
void a_token_free(struct a_token *token);

/**
** Arithmetic lexer context de-allocation function.
** @param lexer Current lexer context to be freed.
*/
void unset_a_lexer(struct a_lexer *a_lexer);

#endif /* ! EXPAND_ARITHMETIC_H */
