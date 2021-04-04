/**
** \file
** \brief Handle linked list of token - Header.
*/

#ifndef TOKEN_H
#define TOKEN_H

/**
** Enumeration of all token types.
*/
enum token_type
{
    END_OF_FILE = 0,
    NEW_LINE,
    SEMI,
    AND,
    OPERATOR,
    RESERVED,
    IO_NUMBER,
    WORD
};

/**
** Enumeration of all operator words.
*/
enum operator_value
{
    DSEMI = 0,
    AND_IF,
    OR_IF,
    L_PARENTHESIS,
    R_PARENTHESIS,
    PIPE,
    DLESSDASH,
    DGREAT,
    DLESS,
    GREATAND,
    LESSAND,
    CLOBBER,
    LESSGREAT,
    GREAT,
    LESS
};

/**
** Enumeration of all reserved words.
*/
enum reserved_words
{
    If = 0,
    Then,
    Else,
    Elif,
    Fi,
    Do,
    Done,
    Case,
    Esac,
    While,
    Until,
    For,
    Lbrace,
    Rbrace,
    Bang,
    In
};

/**
** Contains the token value.
** In the case of END_OF_FILE, NEWLINE, SEMI and AND types
** value is a string set to NULL.
*/
union value
{
    char *str;               ///< is set if type is WORD or IO_NUMBER.
    enum operator_value op;  ///< is set if type is OPERATOR.
    enum reserved_words res; ///< is set if type is RESERVED.
};

/**
** Token structure.
** Contains a token type and a value.
*/
struct token
{
    enum token_type type; ///< token type.
    union value value;    ///< token value.
};


/**
** Gets the value of the string str in the enum reserved_words.
** @param string which may be part of the reserved_words enum.
** @return Return the value of the string str, -1 if it doesn't exist.
*/
int get_reserved_word(const char *str);

/**
** Get the value of the string str in the enum operator_value.
** @param string which may be part of the operator_value enum.
** @return Return the value of the string str, -1 if it doesn't exist.
*/
int get_operator_value(const char *str);

/**
** Creates a new token of type token_type and of value str.
** @param value of the token to create.
** @param type of the token to create.
** @return Return the new created token.
*/
struct token *token_create(char *str, int is_cmd);

/**
** Frees a token.
** @param the token to free.
** @param indicates a pop_command case.
*/
void token_free(struct token *token);

#endif /* ! TOKEN_H */
