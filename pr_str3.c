#include "shell.h"

/**
 * rev_string - Reverses a string.
 *
 * This function reverses the characters in the input string 's'.
 *
 * @s: Input string.
 *
 * Return: No return value.
 */
void rev_string(char *s)
{
	int i, j, c = 0;
	char *str;
	char wait;

	while (c >= 0)
	{
		if (s[c] == '\0')
			break;
		c++;
	}
	str = s;

	for (i = 0; i < (c - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			wait = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = wait;
		}
	}
}
