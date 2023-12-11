#include "shell.h"

/**
 * exit_shell - Exits the shell
 *
 * @datash: Relevant data (args, status)
 * Return: 0 on success.
 */

int exit_shell(data_shell *datash)
{
	int stg_lenght, is_d, is_big;
	unsigned int un_status;

	if (datash->args[1] != NULL)
	{
		un_status = _atoi(datash->args[1]);
		is_d = _isdigit(datash->args[1]);
		stg_lenght = _strlen(datash->args[1]);
		is_big = un_status > (unsigned int)INT_MAX;
		if (!is_d || stg_lenght > 10 || is_big)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (un_status % 256);
	}
	return (0);
}
