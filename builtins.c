#include "shell.h"

/**
 * exec_line - Locates builtins and commands
 *
 * @datash: Relevant data (args)
 * Return: 1 on success.
 */

int exec_line(data_shell *datash)
{
	int (*builtin_sh)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin_sh = get_builtin(datash->args[0]);

	if (builtin_sh != NULL)
		return (builtin_sh(datash));

	return (cmd_exec(datash));
}
