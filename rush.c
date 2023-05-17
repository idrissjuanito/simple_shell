#define _GNU_SOURCE
#include "utils.h"

extern char **environ;
/**
 * main - entry to the shell program
 *
 * @argc: argument count passed to the program
 * @argv: array of argument values passed
 *
 * Return: nothing
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	
	if (!isatty(STDIN_FILENO))
	{
		if (argc > 1)
			return (1);
		non_interact_shell(&line, argv[0]);
	}
	else
	{
		interact_shell(&line, argv[0]);
	}
	free(line);
	exit(EXIT_SUCCESS);
}
