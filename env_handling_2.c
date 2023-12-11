#include "shell.h"

/**
 * _unsetenv - Deletes an environment variable
 *
 *
 * @datash: Relevant data (environment name)
 *
 * Return: 1 on success.
 */

int _unsetenv(data_shell *datash)
{
	char **realloc_env, *v_env, *n_env;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		v_env = _strdup(datash->_environ[i]);
		n_env = _strtok(v_env, "=");
		if (_strcmp(n_env, datash->args[1]) == 0)
		{
			k = i;
		}
		free(v_env);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_env;
	return (1);
}

/**
 * copy_info - Duplicates info to create
 * a new env or alias.
 *
 * @name: Name (env or alias)
 * @value: Value (env or alias)
 *
 * Return: New env or alias.
 */

char *copy_info(char *name, char *value)
{
	int lenght;
	int lenght_name;
	int lenght_value;
	char *new_v;

	lenght_name = _strlen(name);
	lenght_value = _strlen(value);
	lenght = lenght_name + lenght_value + 2;
	new_v = malloc(sizeof(char) * (lenght));
	_strcpy(new_v, name);
	_strcat(new_v, "=");
	_strcat(new_v, value);
	_strcat(new_v, "\0");

	return (new_v);
}

/**
 * set_env - Establishes an environment variable
 *
 * @name: Name of the environment variable
 * @value: Value of the environment variable
 * @datash: Data structure (environ)
 *
 * Return: No return
 */

void set_env(char *name, char *value, data_shell *datash)
{
	char *n_env, *v_env;
	int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		v_env = _strdup(datash->_environ[i]);
		n_env = _strtok(v_env, "=");
		if (_strcmp(n_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = copy_info(n_env, value);
			free(v_env);
			return;
		}
		free(v_env);
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = copy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setenv - Compares environment variable names
 * with the name passed.
 * @datash: Relevant data (env name and env value)
 *
 * Return: 1 on success.
 */

int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}
