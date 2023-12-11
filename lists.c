#include "shell.h"

/**
 * add_sep_node_end - Adds a separator found at the end of a sep_list.
 *
 * This function adds a separator (; | &) found at the end of the sep_list.
 *
 * @head: Head of the linked list.
 * @sep: Separator found (; | &).
 *
 * Return: Address of the head.
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new, *wait;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	wait = *head;

	if (wait == NULL)
	{
		*head = new;
	}
	else
	{
		while (wait->next != NULL)
			wait = wait->next;
		wait->next = new;
	}

	return (*head);
}

/**
 * free_sep_list - Frees a sep_list.
 *
 * This function frees the memory associated with a sep_list.
 *
 * @head: Head of the linked list.
 *
 * Return: No return value.
 */
void free_sep_list(sep_list **head)
{
	sep_list *wait;
	sep_list *acc;

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

/**
 * add_line_node_end - Adds a command line at the end of a line_list.
 *
 * This function adds a command line at the end of the line_list.
 *
 * @head: Head of the linked list.
 * @line: Command line.
 *
 * Return: Address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *wait;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	wait = *head;

	if (wait == NULL)
	{
		*head = new;
	}
	else
	{
		while (wait->next != NULL)
			wait = wait->next;
		wait->next = new;
	}

	return (*head);
}

/**
 * free_line_list - Frees a line_list.
 *
 * This function frees the memory associated with a line_list.
 *
 * @head: Head of the linked list.
 *
 * Return: No return value.
 */
void free_line_list(line_list **head)
{
	line_list *wait;
	line_list *acc;

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
