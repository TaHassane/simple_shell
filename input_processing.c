#include "shell.h"

/**
 * get_line - Reads input from stream
 *
 * @lineptr: Buffer that stores the input
 * @n: Size of lineptr
 * @stream: Stream to read from
 *
 * Return: Number of bytes
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t ret_val;
	static ssize_t inpt;
	char *buf;
	char t = 'z';
	int i;

	if (inpt == 0)
		fflush(stream);
	else
		return (-1);
	inpt = 0;

	buf = malloc(sizeof(char) * BUFSIZE);
	if (buf == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && inpt == 0))
		{
			free(buf);
			return (-1);
		}
		if (i == 0 && inpt != 0)
		{
			inpt++;
			break;
		}
		if (inpt >= BUFSIZE)
			buf = _realloc(buf, inpt, inpt + 1);
		buf[inpt] = t;
		inpt++;
	}
	buf[inpt] = '\0';
	bring_line(lineptr, n, buf, inpt);
	ret_val = inpt;
	if (i != 0)
		inpt = 0;
	return (ret_val);
}

/**
 * bring_line - Assigns the line variable for getline
 *
 * @lineptr: Buffer that stores the input string
 * @buffer: String called to line
 * @n: Size of line
 * @j: Size of buffer
 *
 */

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
