#include "shell.h"

/**
 * add_nodes - Appends separators and command lines to lists
 *
 * @head_s: Pointer to separator list head
 * @head_l: Pointer to command lines list head
 * @input: Input string
 *
 * Return: No return
 */

void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *cur_line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	cur_line = _strtok(input, ";|&");
	do {
		cur_line = swap_char(cur_line, 1);
		add_line_node_end(head_l, cur_line);
		cur_line = _strtok(NULL, ";|&");
	} while (cur_line != NULL);

}

/**
 * swap_char - Swaps | and & with non-printed characters
 *
 * @input: Input string
 * @bool: Type of swap
 * Return: Swapped string
 */

char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * split_line - Tokenizes the input string
 *
 * @input: Input string
 * Return: String after tokenization
 */

char **split_line(char *input)
{
	size_t b_size, i;
	char *token;
	char **tokens;

	b_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (b_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": error allocation\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == b_size)
		{
			b_size += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * b_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": error allocation\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

/**
 * split_commands - Splits command lines based on
 * separators ;, |, and &, and executes them
 *
 *
 * @datash: Data structure
 * @input: Input string
 * Return: 0 to exit, 1 to continue
 */

int split_commands(data_shell *datash, char *input)
{

	int loop;
	line_list *l_head, *l_list;
	sep_list *s_head, *s_list;

	s_head = NULL;
	l_head = NULL;

	add_nodes(&s_head, &l_head, input);

	s_list = s_head;
	l_list = l_head;

	while (l_list != NULL)
	{
		datash->input = l_list->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&s_list, &l_list, datash);

		if (l_list != NULL)
			l_list = l_list->next;
	}

	free_sep_list(&s_head);
	free_line_list(&l_head);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * go_next - Moves to the next stored command line
 *
 * @list_s: Separator list
 * @list_l: Command line list
 * @datash: Data structure
 * Return: No return
 */

void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	line_list *cu_l;
	sep_list *cu_s;
	int sep_loop;

	cu_l = *list_l;
	cu_s = *list_s;
	sep_loop = 1;

	while (cu_s != NULL && sep_loop)
	{
		if (datash->status == 0)
		{
			if (cu_s->separator == '&' || cu_s->separator == ';')
				sep_loop = 0;
			if (cu_s->separator == '|')
				cu_l = cu_l->next, cu_s = cu_s->next;
		}
		else
		{
			if (cu_s->separator == '|' || cu_s->separator == ';')
				sep_loop = 0;
			if (cu_s->separator == '&')
				cu_l = cu_l->next, cu_s = cu_s->next;
		}
		if (cu_s != NULL && !sep_loop)
			cu_s = cu_s->next;
	}

	*list_s = cu_s;
	*list_l = cu_l;
}
