#define _GNU_SOURCE
#include <sys/wait.h>
#include "utils.h"

/**
 * run_cmd - creates a child process and runs command
 *
 * @p: path of the command to run
 * @args: arguments of the command to run
 * @shell: running shell
 *
 * Return: nothing
 */
int run_cmd(char *p, char **args, char *shell)
{
	int status = 0;

	switch (fork())
	{
		case -1:
			exitOnError(shell);
			break;
		case 0:
			execve(p, args, environ);
			exitOnError(shell);
			break;
		default:
			wait(&status);
			break;
	}
	free(p);

	return (status);
}
/**
 * interact_shell - run shell in non interactive mode
 *
 * @line: command to run
 * @shell: shell to program to use
 *
 * Return: nothing
 */
void interact_shell(char **line, char *shell)
{
	size_t len = 0;
	ssize_t cread;
	char *path, *args[100];
	int status = 0;

	while (1)
	{
		clearerr(stdin);
		printf("#cisfun$ ");
		cread = getline(line, &len, stdin);
		if (cread <= 0)
		{
			perror(shell);
			continue;
		}
		if (builtin(*line))
			continue;
		path = parse_cmd(*line, args);
		if (!path)
		{
			perror(shell);
			continue;
		}
		status = run_cmd(path, args, shell);
	}
	exit(status);
}

/**
 * non_interact_shell - run shell in interactive mode
 *
 * @line: address of the command to run
 * @shell: shell program to run the command
 *
 * Return: nothing
 */
void non_interact_shell(char **line, char *shell)
{
	size_t len = 0;
	ssize_t cread = 0;
	char *args[100], *path;
	int status = 0;

	while ((cread = getline(line, &len, stdin)) > 0)
	{
		if (builtin(*line))
			continue;
		path = parse_cmd(*line, args);
		if (!path)
		{
			perror(shell);
			continue;
		}
		run_cmd(path, args, shell);
	}

	exit(status);
}
