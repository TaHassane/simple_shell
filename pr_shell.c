#include "shell.h"

/**
 * cd_shell - Changes the current directory.
 *
 * This function changes the current working directory based on relevant data.
 *
 * @datash: Relevant data.
 *
 * Return: 1 on success, or an appropriate value indicating failure.
 */
int cd_shell(data_shell *datash)
{
	char *dirrectory;
	int home, home2, dash;

	dirrectory = datash->args[1];

	if (dirrectory != NULL)
	{
		home = _strcmp("$HOME", dirrectory);
		home2 = _strcmp("~", dirrectory);
		dash = _strcmp("--", dirrectory);
	}

	if (dirrectory == NULL || !home || !home2 || !dash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", dirrectory) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dirrectory) == 0 || _strcmp("..", dirrectory) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
