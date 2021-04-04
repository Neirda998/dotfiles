/**
** \file
** \brief utility functions for strings - header
**
** Operations on string that may be used in all parts of the project.
*/
#ifndef XSTRING_H
# define XSTRING_H

/**
** Concatenates two string while handling memory.
** @param s1 Prefix String.
** @param s2 Suffix String.
** @return Returns concatenated string.
*/
char *xstrcat(char *s1, char *s2);

/**
** Concatenates a character at the end of a string.
** @param s Prefix String.
** @param c Suffix Character.
** @return Returns concatenated string.
*/
char *xstrcatchar(char *s, char c);

/**
** Checks if a string is a number.
** @param str The string to test.
** @return Returns 1 if the string is a number, else 0.
*/
int is_number(const char *str);

#endif /* ! XSTRING_H */
