#include "shell.h"

/**
 * read_line - Reads input of the string.
 *
 * @i_eof: Return the value of  the getline function
 * Return:  the input string
 */

char *read_line(int *i_eof)
{
	char *user_input = NULL;

	size_t b_size = 0;

	*i_eof = getline(&user_input, &b_size, stdin);

	return (user_input);
}
