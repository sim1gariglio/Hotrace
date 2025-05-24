/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:10:25 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 16:10:26 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

char	*fast_read_line(int capacity, int length, char *result, int i)
{
	char	*line;
	int		status;

	line = NULL;
	while (1)
	{
		status = process_char(&line, &length, &capacity);
		if (status <= 0)
			return (NULL);
		if (status == 2)
			break ;
	}
	result = malloc(length + 1);
	if (!result)
	{
		free (line);
		return (NULL);
	}
	while (i < length)
	{
		result[i] = line[i];
		i++;
	}
	result[length] = '\0';
	return (free (line), result);
}

int	refill_buffer(char buffer[BUFFER_SIZE], int *position, int *bytes_read)
{
	*bytes_read = read(0, buffer, BUFFER_SIZE);
	if (*bytes_read <= 0)
		return (0);
	*position = 0;
	return (1);
}

int	expand_buffer(char **line, int *capacity, int length)
{
	char	*new_line;
	int		i;

	if (*capacity <= 0)
		*capacity = 64;
	else
		*capacity *= 2;
	new_line = malloc(*capacity);
	if (!new_line)
	{
		free (*line);
		return (0);
	}
	i = 0;
	while (i < length)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	free (*line);
	*line = new_line;
	return (1);
}

int	process_char(char **line, int *length, int *capacity)
{
	static char	buffer[BUFFER_SIZE];
	static int	position;
	static int	bytes_read;
	char		c;

	if (position >= bytes_read)
	{
		bytes_read = read(0, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (0);
		position = 0;
	}
	c = buffer[position++];
	if (c == '\n')
		return (2);
	if (*length >= *capacity && !expand_buffer(line, capacity, *length))
		return (-1);
	(*line)[(*length)++] = c;
	return (1);
}
