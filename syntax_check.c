#include "shell.h"

/**
 * repeated_char - Counts the repetitions of a character.
 *
 * This function counts the repetitions of a character in the input string.
 *
 * @input: Input string.
 * @i: Index.
 *
 * Return: The number of repetitions.
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - Finds syntax errors.
 *
 * This function searches for syntax errors in the input string.
 *
 * @input: Input string.
 * @i: Index.
 * @last: Last character read.
 *
 * Return: Index of the error, or 0 when there are no errors.
 */
int error_sep_op(char *input, int i, char last)
{
	int c;

	c = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			c = repeated_char(input, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			c = repeated_char(input, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - Finds the index of the first character.
 *
 * This function searches for the index of the first character
 * in the input string.
 *
 * @input: Input string.
 * @i: Index.
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - Prints a syntax error message.
 *
 * This function prints a message when a syntax error is found.
 *
 * @datash: Data structure.
 * @input: Input string.
 * @i: Index of the error.
 * @bool: Boolean flag to control error message.
 *
 * Return: No return value.
 */
void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	int l;
	char *mess, *mess2, *mess3, *error, *count;

	if (input[i] == ';')
	{
		if (bool == 0)
			mess = (input[i + 1] == ';' ? ";;" : ";");
		else
			mess = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		mess = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		mess = (input[i + 1] == '&' ? "&&" : "&");

	mess2 = ": Syntax error: \"";
	mess3 = "\" unexpected\n";
	count = aux_itoa(datash->count);
	l = _strlen(datash->av[0]) + _strlen(count);
	l += _strlen(mess) + _strlen(mess2) + _strlen(mess3) + 2;

	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(count);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, mess2);
	_strcat(error, mess);
	_strcat(error, mess3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, l);
	free(error);
	free(count);
}

/**
 * check_syntax_error - Intermediate function to find and print
 * a syntax error.
 *
 * This function checks for a syntax error in the input string
 * and prints a message if found.
 *
 * @datash: Data structure.
 * @input: Input string.
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int start = 0;
	int chr = 0;
	int i = 0;

	chr = first_char(input, &start);
	if (chr == -1)
	{
		print_syntax_error(datash, input, start, 0);
		return (1);
	}

	i = error_sep_op(input + start, 0, *(input + start));
	if (i != 0)
	{
		print_syntax_error(datash, input, start + i, 1);
		return (1);
	}

	return (0);
}
