#include "shell.h"

/**
 * shell_loop - Shell loop
 * @datash: Relevant data (av, ur_in, args)
 *
 * Return: No return
 */

void shell_loop(data_shell *datash)
{
	char *ur_in;
	int loop;
	int i_eof;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, ":)) ", 4);
		ur_in = read_line(&i_eof);

		if (i_eof != -1)
		{
			ur_in = without_comment(ur_in);
			if (ur_in == NULL)
				continue;

			if (check_syntax_error(datash, ur_in) == 1)
			{
				datash->status = 2;
				free(ur_in);
				continue;
			}
			ur_in = rep_var(ur_in, datash);
			loop = split_commands(datash, ur_in);
			datash->counter += 1;
			free(ur_in);
		}
		else
		{
			loop = 0;
			free(ur_in);
		}
	}
}

/**
 * without_comment - Removes comments from the input
 *
 * @in: Input string
 * Return: Input without comments
 */

char *without_comment(char *in)
{
	int last_char;
	int i;

	last_char = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				last_char = i;
		}
	}

	if (last_char != 0)
	{
		in = _realloc(in, i, last_char + 1);
		in[last_char] = '\0';
	}

	return (in);
}
