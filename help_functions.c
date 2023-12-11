#include "shell.h"

/**
 * get_help - A function that takes help messages according to builtin
 * @datash: Data structure (args and input)
 * Return: Returns 0
 */

int get_help(data_shell *datash)
{

	if (datash->argmnt[1] == 0)
		aux_help_general();
	else if (_strcmp(datash->argmnt[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(datash->argmnt[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(datash->argmnt[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(datash->argmnt[1], "help") == 0)
		aux_help();
	else if (_strcmp(datash->argmnt[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(datash->argmnt[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(datash->argmnt[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, datash->argmnt[0],
		      _strlen(datash->argmnt[0]));

	datash->status = 0;
	return (1);
}
