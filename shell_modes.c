#define _GNU_SOURCE
#include <sys/wait.h>
#include "utils.h"

/**
 * exec_command - creates a process for executing commands
 *
 * @cmd:  command to run
 * @shell: running shell
 *
 * Return: status returned by child proccess
 */
int exec_command(char **cmd, char *shell)
{
		int status = 0;
		char *path = NULL;

		if (cmd[0][0] == '/' || cmd[0][0] == '.')
			path = check_path(cmd[0]);
		else
			path = find_path(cmd[0]);
		if (!path)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", shell, cmd[0]);
			return (status);
		}
		switch (fork())
		{
			case -1:
				exitOnError(shell);
				break;
			case 0:
				execve(path, cmd, environ);
				exitOnError(shell);
				break;
			default:
				wait(&status);
				break;
		}
		free(path);
	return (status);
}
/**
 * run_cmd - creates a child process and runs command
 *
 * @line: command typed in shell
 * @shell: running shell
 *
 * Return: status of execution
 */
int run_cmd(char *line, char *shell)
{
	int status = 0, i = 0;
	char *args[100], *commands[100];

	if (break_cmd(commands, line, ";") != 0)
		return (status);
	while (commands[i])
	{
		if (break_cmd(args, commands[i], " ") != 0)
		{
			i++;
			continue;
		}
		if (builtin(args, shell))
		{
			i++;
			continue;
		}
		status = exec_command(args, shell);
		i++;
	}
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
		status = run_cmd(*line, shell);
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
	int status = 0;

	while ((cread = getline(line, &len, stdin)) > 0)
		status = run_cmd(*line, shell);

	exit(status);
}
