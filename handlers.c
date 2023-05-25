#include "utils.h"

/*exit_func_t *exit_function[10];*/
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
	if (status >= 0)
		free(*(char **)line);
}

/**
 * handle_signals - handles signals sent to shell
 *
 * @sig: signal to handle
 *
 * Return: nothing
 */
void handle_signals(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_SUCCESS);
}
