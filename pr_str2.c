#include "shell.h"

/**
 * _strdup - Duplicates a string in the heap memory.
 *
 * This function creates a duplicate of the string 's' in the heap memory.
 *
 * @s: Type char pointer, the string to be duplicated.
 *
 * Return: Pointer to the duplicated string, or NULL if memory allocation fails
 */
char *_strdup(const char *s)
{
	size_t l;
	char *nv;

	l = _strlen(s);
	nv = malloc(sizeof(char) * (l + 1));
	if (nv == NULL)
		return (NULL);
	_memcpy(nv, s, l + 1);
	return (nv);
}

/**
 * _strlen - Returns the length of a string.
 *
 * This function calculates and returns the length of the string 's'.
 *
 * @s: Type char pointer, the string.
 *
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int l;

	for (l = 0; s[l] != 0; l++)
	{
	}
	return (l);
}

/**
 * cmp_chars - Compare characters of strings.
 *
 * This function compares characters of the input string 'str'
 * with the specified delimiter.
 *
 * @str: Input string.
 * @delim: Delimiter.
 *
 * Return: 1 if the characters are equal, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - Splits a string by some delimiter.
 *
 * This function splits the input string 'str' using the specified delimiter.
 *
 * @str: Input string.
 * @delim: Delimiter.
 *
 * Return: A pointer to the next token in the string.
 */
char *_strtok(char str[], const char *delim)
{
	unsigned int i, bol;
	static char *split, *strend;
	char *strt;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		split = str; /*Store first address*/
		i = _strlen(str);
		strend = &str[i]; /*Store last address*/
	}
	strt = split;
	if (strt == strend) /*Reaching the end*/
		return (NULL);

	for (bol = 0; *split; split++)
	{
		/*Breaking loop finding the next token*/
		if (split != strt)
			if (*split && *(split - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*split == delim[i])
			{
				*split = '\0';
				if (split == strt)
					strt++;
				break;
			}
		}
		if (bol == 0 && *split) /*Str != Delim*/
			bol = 1;
	}
	if (bol == 0) /*Str == Delim*/
		return (NULL);
	return (strt);
}

/**
 * _isdigit - Determines if a string represents a number.
 *
 * This function checks if the input string 's' represents a number.
 *
 * @s: Input string.
 *
 * Return: 1 if the string is a number, 0 otherwise.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
