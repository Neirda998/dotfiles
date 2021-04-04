/**
** \file
** Quote managment functions.
*/

#ifndef QUOTE_LEN_H
# define QUOTE_LEN_H

/**
** Enumeration of all quote types possible.
*/
enum quote_type
{
    NONE = 0,
    DOUBLE,
    SIMPLE,
    COMMAND,
    MATH_L,
    SUB_L,
    VAR_L,
    MATH_R,
    SUB_R,
    VAR_R
};

/**
** Checks if string str begins with the string key.
** @param str The string to compare.
** @param key The keys to check.
** @return Returns 1 if str begins with key, else 0.
*/
int begin_with(char *str, char *key);

/**
** Checks if a string begin with a type of quotes and returns it.
** @param str The string to test.
** @return Returns the type of quote.
*/
enum quote_type is_quote(char *str);

/**
** Gives the length of a given quote type.
** @param type The type of a quote.
** @return Returns the length of the quote in param.
*/
int quote_len(enum quote_type type);

#endif /* ! QUOTE_LEN_H */
