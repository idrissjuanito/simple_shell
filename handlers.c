#include "utils.h"

exit_func_t *exit_function[10];
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
 * _on_exit - terminates the shell
 *
 * @exit_func: pointer to function handler
 * @args: arguments to pass to function
 *
 * Return: nothing
 */
void _on_exit(void (*exit_func)(int, void *), void *args)
{
	static int reg;
	exit_func_t *f = malloc(sizeof(exit_func_t));

	f->func_name = exit_func;
	f->args = args;
	exit_function[reg] = f;
	reg++;
}

/**
 * exit_ - exit function to terminate a shel
 *
 * @status: termination status
 *
 * Return: nothing
 */
void exit_(int status)
{
	int i = 0;
	void (*func)(int, void *);
	void *args;

	while (exit_function[i])
	{
		func = exit_function[i]->func_name;
		args = exit_function[i]->args;
		func(status, args);
		free(exit_function[i]);
		i++;
	}
	fflush(stdout);
	fflush(stdin);
	fflush(stderr);
	_exit(status);
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
		exit(EXIT_SUCCESS);
}
