#include "shell.h"

/**
 * add_rvar_node - Adds a variable at the end of a r_var list.
 *
 * This function adds a variable at the end of the r_var list.
 *
 * @head: Head of the linked list.
 * @lvar: Length of the variable.
 * @val: Value of the variable.
 * @lval: Length of the value.
 *
 * Return: Address of the head.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *wait, *nv;

	nv = malloc(sizeof(r_var));
	if (nv == NULL)
		return (NULL);

	nv->len_var = lvar;
	nv->val = val;
	nv->len_val = lval;

	nv->next = NULL;
	wait = *head;

	if (wait == NULL)
	{
		*head = nv;
	}
	else
	{
		while (wait->next != NULL)
			wait = wait->next;
		wait->next = nv;
	}

	return (*head);
}

/**
 * free_rvar_list - Frees a r_var list.
 *
 * This function frees the memory associated with a r_var list.
 *
 * @head: Head of the linked list.
 *
 * Return: No return value.
 */
void free_rvar_list(r_var **head)
{
	r_var *acc, *wait;

	if (head != NULL)
	{
		acc = *head;
		while ((wait = acc) != NULL)
		{
			acc = acc->next;
			free(wait);
		}
		*head = NULL;
	}
}
