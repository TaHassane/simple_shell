#include "shell.h"

/**
 * get_error - Calls the error according to the builtin, syntax, or permission
 * @datash: Data structure containing arguments
 * @eval: Error value
 * Return: Error
 */

int get_error(data_shell *datash, int eval)
{
	char *error_msg;

	switch (eval)
	{
	case -1:
		error_msg = error_env(datash);
		break;
	case 126:
		error_msg = error_path_126(datash);
		break;
	case 127:
		error_msg = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error_msg = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error_msg = error_get_cd(datash);
		break;
	}

	if (error_msg)
	{
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		free(error_msg);
	}

	datash->status = eval;
	return (eval);
}
