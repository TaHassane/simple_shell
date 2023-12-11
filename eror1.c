#include "shell.h"

/**
 * strcat_cd - Concatenates a message for a directory change error.
 *
 * This function combines the provided directory information,
 * message, error output,and a counter for lines
 * to create an error message related to changing directories.
 *
 * @datash: Relevant data (directory information).
 * @msg: Message to be included in the error.
 * @error: Output message containing the error details.
 * @ver_str: Counter for lines.
 *
 * Return: The error message after concatenation.
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *flag_x;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		flag_x = malloc(3);
		flag_x[0] = '-';
		flag_x[1] = datash->args[1][1];
		flag_x[2] = '\0';
		_strcat(error, flag_x);
		free(flag_x);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - Generates an error message for the cd command in get_cd.
 *
 * This function creates an error message specific to
 * the cd command in the get_cd function,
 * incorporating relevant directory data.
 *
 * @datash: Relevant data (directory information).
 *
 * Return: The generated error message.
 */
char *error_get_cd(data_shell *datash)
{
	char *error, *ver_str, *msg;
	int l, id_l;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		id_l = 2;
	}
	else
	{
		msg = ": can't cd to ";
		id_l = _strlen(datash->args[1]);
	}

	l = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	l += _strlen(ver_str) + _strlen(msg) + id_l + 5;
	error = malloc(sizeof(char) * (l + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - Generates a generic error message for command not found.
 *
 * This function creates a generic error message for a command not being found,
 * incorporating relevant data such as counters and arguments.
 *
 * @datash: Relevant data (counter, arguments).
 *
 * Return: The generated error message.
 */
char *error_not_found(data_shell *datash)
{
	int l;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	l = _strlen(datash->av[0]) + _strlen(ver_str);
	l += _strlen(datash->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell - Generates a generic error message for exit in get_exit.
 *
 * This function creates a generic error message
 * for the exit command in the get_exit function,
 * incorporating relevant data such as counters and arguments.
 *
 * @datash: Relevant data (counter, arguments).
 *
 * Return: The generated error message.
 */
char *error_exit_shell(data_shell *datash)
{
	int l;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	l = _strlen(datash->av[0]) + _strlen(ver_str);
	l += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
