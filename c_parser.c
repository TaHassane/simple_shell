#include "shell.h"

/**
 * get_builtin - Builtin that parses the command in the argument
 * @cmd: Command
 * Return: Function pointer of the builtin command
 */

int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};

	int k;

	for (k = 0; builtin[k].name; k++)
	{
		if (_strcmp(builtin[k].name, cmd) == 0)
			break;
	}

	return (builtin[k].f);
}
