#include "shell.h"

/**
 * is_cdir - Checks if ":" is in the current directory.
 *
 * This function checks if ":" is present in the path
 * indicating the current directory.
 *
 * @path: Type char pointer to the path string.
 * @i: Type int pointer to the index.
 *
 * Return: 1 if the path is searchable in the current directory,
 * 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - Locates a command.
 *
 * This function locates the location of the specified command
 * in the environment.
 *
 * @cmd: Command name.
 * @_environ: Environment variable.
 *
 * Return: The location of the command.
 */
char *_which(char *cmd, char **_environ)
{
	int l_dirr, l_cmd, i;
	char *path, *path_p, *token, *dirrectory;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		path_p = _strdup(path);
		l_cmd = _strlen(cmd);
		token = _strtok(path_p, ":");
		i = 0;
		while (token != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			l_dirr = _strlen(token);
			dirrectory = malloc(l_dirr + l_cmd + 2);
			_strcpy(dirrectory, token);
			_strcat(dirrectory, "/");
			_strcat(dirrectory, cmd);
			_strcat(dirrectory, "\0");
			if (stat(dirrectory, &st) == 0)
			{
				free(path_p);
				return (dirrectory);
			}
			free(dirrectory);
			token = _strtok(NULL, ":");
		}
		free(path_p);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - Determines if a file is executable.
 *
 * This function checks if the file specified
 * in the data structure is executable.
 *
 * @datash: Data structure.
 *
 * Return: 0 if the file is not executable, another number if it is.
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - Verifies if the user has permissions to access.
 *
 * This function checks if the user has permissions
 * to access the specified destination directory.
 *
 * @dirrectory: Destination directory.
 * @datash: Data structure.
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int check_error_cmd(char *dirrectory, data_shell *datash)
{
	if (dirrectory == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dirrectory) != 0)
	{
		if (access(dirrectory, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dirrectory);
			return (1);
		}
		free(dirrectory);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - Executes command lines.
 *
 * This function executes command lines
 * based on relevant data (arguments and input).
 *
 * @datash: Relevant data structure containing arguments and input.
 *
 * Return: 1 on success.
 */
int cmd_exec(data_shell *datash)
{
	int st, ex;
	pid_t pd;
	pid_t wpd;
	char *dirrectory;
	(void) wpd;

	ex = is_executable(datash);
	if (ex == -1)
		return (1);
	if (ex == 0)
	{
		dirrectory = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(dirrectory, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (ex == 0)
			dirrectory = _which(datash->args[0], datash->_environ);
		else
			dirrectory = datash->args[0];
		execve(dirrectory + ex, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &st, WUNTRACED);
		} while (!WIFEXITED(st) && !WIFSIGNALED(st));
	}

	datash->status = st / 256;
	return (1);
}
