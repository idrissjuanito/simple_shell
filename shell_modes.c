#define _GNU_SOURCE
#include <sys/wait.h>
#include "utils.h"


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
		printf("($) ");
		cread = _getline(line, &len, stdin);
		if (cread <= 0)
			continue;
		if (strcmp(*line, "exit\n") == 0)
		{
			exit(98);
		}
		path = parse_cmd(*line, args);
		if (!path)
		{
			perror(args[0]);
			continue;
		}
		switch (fork())
		{
			case -1:
				exitOnError(shell, args[0]);
				break;
			case 0:
				execve(path, args, environ);
				exitOnError(shell, args[0]);
				break;
			default:
				wait(&status);
				break;
		}
		free(path);
	}
	exit(98);
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
	char **const envp = environ;
	int status = 0;

	while ((cread = _getline(line, &len, stdin)) > 0)
	{
		path = parse_cmd(*line, args);
		if (!path)
			exitOnError(shell, *line);
		switch (fork())
		{
			case -1:
				exitOnError(shell, args[0]);
				break;
			case 0:
				execve(path, args, envp);
				exitOnError(shell, args[0]);
				break;
			default:
				wait(&status);
				break;
		}
		free(path);
	}
	free(*line);
	exit(status);
}