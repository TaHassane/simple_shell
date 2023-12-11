#include "shell.h"

/**
 * error_env - Generates an error message for env in get_env.
 *
 * This function creates an error message specific
 * to the env command in the get_env function,
 * incorporating relevant data such as counters and arguments.
 *
 * @datash: Relevant data (counter, arguments).
 *
 * Return: The generated error message.
 */
char *error_env(data_shell *datash)
{
	char *error;
	int l;
	char *msg;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	l = _strlen(datash->av[0]) + _strlen(ver_str);
	l += _strlen(datash->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126 - Generates an error message
 * for path failure due to denied permission.
 *
 * This function creates an error message specific
 * to path failure (126 error code)
 * caused by denied permission,
 * incorporating relevant data such as counters and arguments.
 *
 * @datash: Relevant data (counter, arguments).
 *
 * Return: The generated error message.
 */
char *error_path_126(data_shell *datash)
{
	char *error;
	int l;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	l = _strlen(datash->av[0]) + _strlen(ver_str);
	l += _strlen(datash->args[0]) + 24;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
