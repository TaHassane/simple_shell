#include "shell.h"

/**
 * get_len - Get the length of a number.
 *
 * This function calculates the length of the integer 'n'.
 *
 * @n: Integer number.
 *
 * Return: Length of the number.
 */
int get_len(int n)
{
	int l = 1;
	unsigned int x;

	if (n < 0)
	{
		l++;
		x = n * -1;
	}
	else
	{
		x = n;
	}
	while (x > 9)
	{
		l++;
		x = x / 10;
	}

	return (l);
}
/**
 * aux_itoa - Converts an integer to a string.
 *
 * This function converts the integer 'n' to its string representation.
 *
 * @n: Integer number.
 *
 * Return: The resulting string.
 */
char *aux_itoa(int n)
{
	unsigned int x;
	int l = get_len(n);
	char *buff;

	buff = malloc(sizeof(char) * (l + 1));
	if (buff == 0)
		return (NULL);

	*(buff + l) = '\0';

	if (n < 0)
	{
		x = n * -1;
		buff[0] = '-';
	}
	else
	{
		x = n;
	}

	l--;
	do {
		*(buff + l) = (x % 10) + '0';
		x = x / 10;
		l--;
	}
	while (x > 0)
		;
	return (buff);
}

/**
 * _atoi - Converts a string to an integer.
 *
 * This function converts the input string 's' to an integer.
 *
 * @s: Input string.
 *
 * Return: The resulting integer.
 */
int _atoi(char *s)
{
	unsigned int i, c = 0, size = 0, w = 0;
	unsigned int y = 1, m = 1;

	while (*(s + c) != '\0')
	{
		if (size > 0 && (*(s + c) < '0' || *(s + c) > '9'))
			break;

		if (*(s + c) == '-')
			y *= -1;

		if ((*(s + c) >= '0') && (*(s + c) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		c++;
	}

	for (i = c - size; i < c; i++)
	{
		w = w + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (w * y);
}
