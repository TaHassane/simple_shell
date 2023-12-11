#include "shell.h"

/**
 * cd_dot - Changes to the parent directory.
 *
 * This function changes the current working directory
 * to the parent directory.
 *
 * @datash: Relevant data (environment variables).
 *
 * Return: No return value.
 */
void cd_dot(data_shell *datash)
{
	char *dirrectory, *pwd_cp, *strtok_cp_pwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pwd_cp = _strdup(pwd);
	set_env("OLDPWD", pwd_cp, datash);
	dirrectory = datash->args[1];
	if (_strcmp(".", dirrectory) == 0)
	{
		set_env("PWD", pwd_cp, datash);
		free(pwd_cp);
		return;
	}
	if (_strcmp("/", pwd_cp) == 0)
	{
		free(pwd_cp);
		return;
	}
	strtok_cp_pwd = pwd_cp;
	rev_string(strtok_cp_pwd);
	strtok_cp_pwd = _strtok(strtok_cp_pwd, "/");
	if (strtok_cp_pwd != NULL)
	{
		strtok_cp_pwd = _strtok(NULL, "\0");

		if (strtok_cp_pwd != NULL)
			rev_string(strtok_cp_pwd);
	}
	if (strtok_cp_pwd != NULL)
	{
		chdir(strtok_cp_pwd);
		set_env("PWD", strtok_cp_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(pwd_cp);
}

/**
 * cd_to - Changes to a directory given by the user.
 *
 * This function changes the current working directory
 * to the specified directory.
 *
 * @datash: Relevant data (directories).
 *
 * Return: No return value.
 */
void cd_to(data_shell *datash)
{
	char *dirrectory, *pwd_cp, *dirr_cp;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));

	dirrectory = datash->args[1];
	if (chdir(dirrectory) == -1)
	{
		get_error(datash, 2);
		return;
	}

	pwd_cp = _strdup(pwd);
	set_env("OLDPWD", pwd_cp, datash);

	dirr_cp = _strdup(dirrectory);
	set_env("PWD", dirr_cp, datash);

	free(pwd_cp);
	free(dirr_cp);

	datash->status = 0;

	chdir(dirrectory);
}

/**
 * cd_previous - Changes to the previous directory.
 *
 * This function changes the current working directory
 * to the previous directory.
 *
 * @datash: Relevant data (environment variables).
 *
 * Return: No return value.
 */
void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *pwd_p, *old, *pwd_cp, *old_cp;

	getcwd(pwd, sizeof(pwd));
	pwd_cp = _strdup(pwd);

	old = _getenv("OLDPWD", datash->_environ);

	if (old == NULL)
		old_cp = pwd_cp;
	else
		old_cp = _strdup(old);

	set_env("OLDPWD", pwd_cp, datash);

	if (chdir(old_cp) == -1)
		set_env("PWD", pwd_cp, datash);
	else
		set_env("PWD", old_cp, datash);

	pwd_p = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, pwd_p, _strlen(pwd_p));
	write(STDOUT_FILENO, "\n", 1);

	free(pwd_cp);
	if (old)
		free(old_cp);

	datash->status = 0;

	chdir(pwd_p);
}

/**
 * cd_to_home - Changes to the home directory.
 *
 * This function changes the current working directory
 * to the user's home directory.
 *
 * @datash: Relevant data (environment variables).
 *
 * Return: No return value.
 */
void cd_to_home(data_shell *datash)
{
	char *pwd_p, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pwd_p = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", pwd_p, datash);
		free(pwd_p);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(pwd_p);
		return;
	}

	set_env("OLDPWD", pwd_p, datash);
	set_env("PWD", home, datash);
	free(pwd_p);
	datash->status = 0;
}
