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
		printf("#cisfun$ ");
		cread = getline(line, &len, stdin);
		if (cread <= 0)
		{
			perror(shell);
			fflush(stdout);
			continue;
		}
		/*if (strcmp(*line, "exit\n") == 0)*/
		/*{*/
			/*exit(98);*/
		/*}*/
		path = parse_cmd(*line, args);
		if (!path)
			continue;
		switch (fork())
		{
			case -1:
				exitOnError(shell);
				break;
			case 0:
				execve(path, args, environ);
				exitOnError(shell);
				break;
			default:
				wait(&status);
				break;
		}
		free(path);
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
	char **const envp = environ;
	int status = 0;

	while ((cread = getline(line, &len, stdin)) > 0)
	{
		path = parse_cmd(*line, args);
		if (!path)
			continue;
		switch (fork())
		{
			case -1:
				exitOnError(shell);
				break;
			case 0:
				execve(path, args, envp);
				exitOnError(shell);
				break;
			default:
				wait(&status);
				break;
		}
		free(path);
	}
	exit(status);
}
