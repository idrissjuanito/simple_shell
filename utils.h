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
char *parse_cmd(char *line, char **args);
void interact_shell(char **line, char *shell);
void non_interact_shell(char **line, char *shell);
void exitOnError(char *shell, char *cmd);
char *find_path(char *cmd);
void handle_signals(int sig);
void handle_exit(int status, void *line);
ssize_t _getline(char **line, size_t *len, FILE *stream);
#endif
