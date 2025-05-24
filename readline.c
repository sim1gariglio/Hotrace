/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:55:18 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 18:55:20 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static char	*rl_expand_line(char *line, int *capacity, int length)
{
	int		new_capacity;
	char	*new_line;
	int		i;

	if (*capacity < 64)
		new_capacity = 64;
	else
		new_capacity = *capacity * 2;
	new_line = malloc(new_capacity);
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < length)
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	*capacity = new_capacity;
	return (new_line);
}

static char	*rl_finalize_line(char *line, int length)
{
	char	*result;
	int		i;

	result = malloc(length + 1);
	if (!result)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		result[i] = line[i];
		i++;
	}
	result[length] = '\0';
	free(line);
	return (result);
}

static int	rl_fill_line(char **line, int *length, int *capacity, t_buffer buf)
{
	char	c;

	while (1)
	{
		c = buf.data[(*buf.pos)++];
		if (c == '\n')
			return (1);
		if (*length >= *capacity)
		{
			*line = rl_expand_line(*line, capacity, *length);
			if (!*line)
				return (0);
		}
		(*line)[(*length)++] = c;
		if (*buf.pos >= *buf.bytes)
			return (2);
	}
}

static int	rl_process_status(int status, t_buffer *buf)
{
	if (status == 1)
		return (1);
	if (status == 0)
		return (0);
	if (status == 2)
	{
		if (rl_reload_buffer(buf->data, buf->pos, buf->bytes) <= 0)
			return (1);
	}
	return (2);
}

char	*fast_read_line(int capacity, int length, int status, int result)
{
	static char	buffer[BUFFER_SIZE];
	static int	position = 0;
	static int	bytes_read = 0;
	char		*line;
	t_buffer	buf;

	line = NULL;
	buf = (t_buffer){buffer, &position, &bytes_read};
	if (position >= bytes_read)
		if (rl_reload_buffer(buffer, &position, &bytes_read) <= 0)
			return (NULL);
	while (1)
	{
		status = rl_fill_line(&line, &length, &capacity, buf);
		result = rl_process_status(status, &buf);
		if (result <= 1)
			break ;
	}
	return (rl_finalize_line(line, length));
}
