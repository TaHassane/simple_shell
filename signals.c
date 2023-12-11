#include "shell.h"

/**
 * get_sigint - Handles the ctrl + c call in the prompt
 * @sig: Signal handler
 */

void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n:)) ", 5);
}
