#include "shell.h"

/**
 * check_vars - Verifies if the typed variable is $$ or $?
 *
 * @h: Head of the linked list
 * @in: Input string
 * @st: Last status of the Shell
 * @data: Data structure
 * Return: No return
 */

int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int l_sts;
	int l_pid;
	int i;

	l_pid = _strlen(data->pid);
	l_sts = _strlen(st);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node(h, 2, st, l_sts), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, l_pid), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * check_env - Checks if the typed variable is an environment variable
 *
 * @h: Head of linked list
 * @in: Input string
 * @data: Data structure
 * Return: No return
 */

void check_env(r_var **h, char *in, data_shell *data)
{
	char **env_rows;
	int chr, len_v, j, row_i;

	env_rows = data->_environ;
	for (row_i = 0; env_rows[row_i]; row_i++)
	{
		for (j = 1, chr = 0; env_rows[row_i][chr]; chr++)
		{
			if (env_rows[row_i][chr] == '=')
			{
				len_v = _strlen(env_rows[row_i] + chr + 1);
				add_rvar_node(h, j, env_rows[row_i] + chr + 1, len_v);
				return;
			}

			if (in[j] == env_rows[row_i][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * rep_var - Calls functions to replace variables in the string
 *
 * @input: Input string
 * @datash: Data structure
 * Return: Replaced string
 */

char *rep_var(char *input, data_shell *datash)
{
	r_var *r_head, *c_node;
	char *status;
	char *new_input;
	int or_l;
	int nw_l;

	status = aux_itoa(datash->status);
	r_head = NULL;

	or_l = check_vars(&r_head, input, status, datash);

	if (r_head == NULL)
	{
		free(status);
		return (input);
	}

	c_node = r_head;
	nw_l = 0;

	while (c_node != NULL)
	{
		nw_l += (c_node->len_val - c_node->len_var);
		c_node = c_node->next;
	}

	nw_l += or_l;

	new_input = malloc(sizeof(char) * (nw_l + 1));
	new_input[nw_l] = '\0';

	new_input = replaced_input(&r_head, input, new_input, nw_l);

	free(input);
	free(status);
	free_rvar_list(&r_head);

	return (new_input);
}

/**
 * replaced_input - Replaces variables in the input string
 *
 * @head: Head of the linked list
 * @input: Input string
 * @new_input: New input string (after replacement)
 * @nlen: New length
 * Return: Replaced string
 */

char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	int i, j, k;
	r_var *c_node;

	c_node = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(c_node->len_var) && !(c_node->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (c_node->len_var && !(c_node->len_val))
			{
				for (k = 0; k < c_node->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < c_node->len_val; k++)
				{
					new_input[i] = c_node->val[k];
					i++;
				}
				j += (c_node->len_var);
				i--;
			}
			c_node = c_node->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}
