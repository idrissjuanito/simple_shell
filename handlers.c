#include "utils.h"

/**
 * handle_exit - runs when the exit function is called
 *
 * @status: status sent by exit function
 * @line: memory address to be freed
 *
 * Return: nothing
 */
void handle_exit(int status, void *line)
{
	free(*(char **)line);
	printf("exiting with status: %d\n", status);
}

/**
 * handle_signals - handle some signals
 *
 * @sig: signal to handle
 *
 * Return: void
 */
void handle_signals(int sig)
{
	if (sig == SIGINT)
		exit(98);
}
