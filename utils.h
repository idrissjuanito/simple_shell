#ifndef UTILS_H
#define UTILS_H
#define _GNU_SOURCE
#define BSDSOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
extern char **environ;
/**
 * struct exit_func - exit function handlers types
 *
 * @func_name: name of func handler
 * @args: args of the exit handler
 */
typedef struct exit_func
{
	void (*func_name)(int, void *);
	void *args;
} exit_func_t;
void _on_exit(void (*exit_func)(int, void *), void *args);
void exit_(int status);
char *parse_cmd(char **args);
void interact_shell(char **line, char *shell);
void non_interact_shell(char **line, char *shell);
void exitOnError(char *shell);
char *find_path(char *cmd);
char *trim_string(char *cmd);
void break_cmd(char **args, char *cmd);
void handle_signals(int sig);
void handle_exit(int status, void *line);
ssize_t _getline(char **line, size_t *len, FILE *stream);
int builtin(char *cmd, char **args, char *shell);
#endif
