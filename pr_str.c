#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 *
 * This function concatenates the string pointed to by 'src'
 * to the end of the string pointed to by 'dest'.
 *
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 *
 * This function copies the string pointed to by 'src' to the location
 * pointed to by 'dest'.
 *
 * @dest: Type char pointer, the destination of the copied string.
 * @src: Type char pointer, the source string to be copied.
 *
 * Return: The destination string.
 */
char *_strcpy(char *dest, char *src)
{

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}
/**
 * _strcmp - Compares two strings.
 *
 * This function compares the strings pointed to by 's1' and 's2'.
 *
 * @s1: Pointer to the first string to be compared.
 * @s2: Pointer to the second string to be compared.
 *
 * Return: 0 if the strings are equal, otherwise a non-zero value.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - Locates a character in a string.
 *
 * This function searches for the first occurrence of the character 'c'
 * in the string 's'.
 *
 * @s: Pointer to the string.
 * @c: Character to locate.
 *
 * Return: Pointer to the first occurrence of the character 'c' in 's',
 * or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - Gets the length of a prefix substring.
 *
 * This function calculates the length of the initial
 * segment of the string 's' consisting
 * of only characters from the string 'accept'.
 *
 * @s: Initial segment string.
 * @accept: Accepted bytes.
 *
 * Return: The number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int bol, i, j;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bol = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bol = 0;
				break;
			}
		}
		if (bol == 1)
			break;
	}
	return (i);
}
