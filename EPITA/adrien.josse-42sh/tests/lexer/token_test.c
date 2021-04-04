#include <criterion/criterion.h>
#include <stddef.h>
#include <stdio.h>

#include "lexer/token.h"

Test(get_reserved_words, all_values)
{
    char *reserved_words[16] =
    {
        "if", "then", "else", "elif", "fi", "do", "done", "case", "esac",
        "while", "until", "for", "{", "}", "!", "in"
    };

    for (size_t i = 0; i < sizeof(reserved_words) / sizeof(char*); ++i)
        cr_expect_eq(get_reserved_word(reserved_words[i]), i);

    cr_expect_eq(get_reserved_word("If"), -1);
}

Test(get_operator_values, all_values)
{
    char *operator_values[] =
    {
        ";;", "&&", "||", "(", ")", "|", "<<-",">>", "<<",  ">&", "<&", ">|",
        "<>", ">", "<"
    };

    for (size_t i = 0; i < sizeof(operator_values) / sizeof(char*); ++i)
        cr_expect_eq(get_operator_value(operator_values[i]), i);

    cr_expect_eq(get_operator_value("&|"), -1);
}

Test(token_create, END_OF_FILE)
{
    // Given
    char *str = strdup("");
    enum token_type type = END_OF_FILE;
    // When
    struct token *token = token_create(str, 0);
    // Then
    cr_expect_not_null(token);
    cr_expect_eq(token->type, type);

    token_free(token);
}

Test(token_create, WORD)
{
    // Given
    char *str = strdup("foo");
    enum token_type type = WORD;
    // When
    struct token *token = token_create(str, 0);
    // Then
    cr_expect_not_null(token);
    cr_expect_eq(token->type, type);
    cr_expect_str_eq(token->value.str, str);

    token_free(token);
}

Test(token_create, IO_NUMBER)
{
    // Given
    char *str = strdup("42");
    enum token_type type = IO_NUMBER;
    // When
    struct token *token = token_create(str, 0);
    // Then
    cr_expect_not_null(token);
    cr_expect_eq(token->type, type);
    cr_expect_str_eq(token->value.str, "42");

    token_free(token);
}

Test(token_create, OPERATOR)
{
    // Given
    char *str = strdup("&&");
    enum token_type type = OPERATOR;
    // When
    struct token *token = token_create(str, 0);
    // Then
    cr_expect_not_null(token);
    cr_expect_eq(token->type, type);
    cr_expect_eq(token->value.op, AND_IF);

    token_free(token);
}

Test(token_create, RESERVED)
{
    // Given
    char *str = strdup("case");
    enum token_type type = RESERVED;
    // When
    struct token *token = token_create(str, 0);
    // Then
    cr_expect_not_null(token);
    cr_expect_eq(token->type, type);
    cr_expect_eq(token->value.res, Case);

    token_free(token);
}
