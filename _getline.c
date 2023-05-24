#define _GNU_SOURCE
#include <errno.h>
#include "utils.h"

#define BUFSIZE 1024

/**
 * init_params - initialises the line buffer
 *
 * @line: address to hold buffer
 * @len: lenght of buffer
 *
 * Return: address of the buffer
 */
char *init_params(char **line, size_t *len)
{
	if (!line || !len)
		return (NULL);
	if (!*line && !*len)
	{
		*line = malloc(BUFSIZE * sizeof(char) + 1);
		if (!*line)
			return (NULL);
		*len =	BUFSIZE;
	}
	return (*line);
}
/**
 * update_line - writes character in buffer and checks for end of line
 *
 * @c: character to write
 * @lin: address to write at
 *
 * Return: 0 if new line found or 1
 */
int update_line(char c, char **lin)
{
	char *line = *lin;

	if (c == '\n')
	{
		*line = c;
		return (0);
	}
	*line = c;
	return (1);
}
/**
 * _getline - reads a line from a stream
 *
 * @line: pointer to a buffer for storing the line data
 * @len: length of the line buffer
 * @stream: source of data to read
 *
 * Return: number of characters read
 */
ssize_t _getline(char **line, size_t *len, FILE *stream)
{
	int i = 0, fd;
	ssize_t reads = 0;
	size_t j = 0;
	static off_t offset;
	char buf[BUFSIZE], *line_buf;

	line_buf = init_params(line, len);
	if (!line_buf)
		return (-1);
	fd = fileno(stream);
	lseek(fd, offset, SEEK_SET);
	while ((reads = read(fd, buf, BUFSIZE)) > 0)
	{
		for (i = 0; i <= reads; i++)
		{
			if (j == *len)
			{
				*len += BUFSIZE;
				*line = realloc(*line, *len);
				if (!*line)
					return (-1);
				line_buf += j;
			}
			if (update_line(buf[i], &line_buf) == 0)
				break;
			j++;
			line_buf++;
		}
		if (buf[i] == '\n')
			break;
	}
	if (reads < 1)
		return (-1);
	*(line_buf + 1)  = '\0';
	offset += ++j + 1;
	close(fd);
	return (j);
}
