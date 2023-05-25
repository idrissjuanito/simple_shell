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

void _on_exit(void (*exit_func)(int, void *), void *args)
{
	static int reg;
	exit_func_t *f = malloc( sizeof(exit_func_t));
	f->func_name = exit_func;
	f->args = args;
	exit_function[reg] = f;
	reg++;
}
void exit_(int status)
{
	int i = 0;
	void (*func)(int, void *);
	void *args;

	if (exit_function[i])
	{
		func = exit_function[i]->func_name;	
		args = exit_function[i]->args;
		func(status, args);
		free(exit_function[i]);
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
		exit_(98);
}
