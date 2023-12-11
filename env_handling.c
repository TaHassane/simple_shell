#include "shell.h"

/**
 * cmp_env_name - Compares env variable names
 * with the passed name.
 * @nenv: Name of the environment variable
 * @name: Passed name
 *
 * Return: 0 if not equal; otherwise, another value.
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - Gets an environment variable
 * @name: Name of the environment variable
 * @_environ: Environment variable
 *
 * Return: Value of the environment variable if found;
 * Otherwise, returns NULL.
 */

char *_getenv(const char *name, char **_environ)
{
	int i;
	int mv;
	char *env_pntr;

	env_pntr = NULL;
	mv = 0;

	for (i = 0; _environ[i]; i++)
	{
		mv = cmp_env_name(_environ[i], name);
		if (mv)
		{
			env_pntr = _environ[i];
			break;
		}
	}

	return (env_pntr + mv);
}

/**
 * _env - Prints the environment variables
 *
 * @datash: Relevant data
 *
 * Return: 1 on success.
 */

int _env(data_shell *datash)
{
	int i;
	int j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
