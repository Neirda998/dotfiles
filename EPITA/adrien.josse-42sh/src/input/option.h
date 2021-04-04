/**
** \file
** Header of option parser.
*/
#ifndef OPTION_H
# define OPTION_H

/**
** Struct containing the value of the command line options of 42sh.
*/
struct opt
{
    int index;
    int is_c;
    char *c_string;   ///< String given to the command line if c is set
    int is_norc;
    int is_noclobber;
    int is_ast_print;
    int shopt[8];     /**< Int array matching the 8 different shopt
                         possibilities in the subject order.
                         0, means no change.
                         1, means set.
                         -1 means unset. */
};
/**
** Option parser
** @param ac Number of arguments given to the command line.
** @param av Arguments given to the command line.
** @return A struct containing the value of the command line options of 42sh.
*/
struct opt *parse_options(int ac, char **av);

/**
** Struct option de-allocator.
** @param ac Number of arguments given to the command line
** @return A struct containing the value of the command line options of 42sh.
*/
void free_options(struct opt *opt);

#endif /* ! OPTION_H */
