/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseInput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:55:15 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 18:55:16 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static t_map	*expand_entries(t_map *entries, int *capacity, int count)
{
	int		i;
	int		new_capacity;
	t_map	*new_entries;

	i = 0;
	new_capacity = (*capacity) * 2;
	new_entries = malloc(new_capacity * sizeof(t_map));
	if (!new_entries)
		return (NULL);
	while (i < count)
	{
		new_entries[i].key = entries[i].key;
		new_entries[i].value = entries[i].value;
		i++;
	}
	free(entries);
	*capacity = new_capacity;
	return (new_entries);
}

static t_map	*shrink_entries(t_map *entries, int count)
{
	int		i;
	t_map	*final_entries;

	i = 0;
	final_entries = malloc(count * sizeof(t_map));
	if (!final_entries)
		return (entries);
	while (i < count)
	{
		final_entries[i].key = entries[i].key;
		final_entries[i].value = entries[i].value;
		i++;
	}
	free(entries);
	return (final_entries);
}

static int	read_key_value_pair(t_map *entries, int count)
{
	char	*key;
	char	*val;

	key = fast_read_line(0, 0, 0, 0);
	if (!key || key[0] == '\0')
	{
		free(key);
		return (-1);
	}
	val = fast_read_line(0, 0, 0, 0);
	if (!val)
	{
		free(key);
		return (-1);
	}
	entries[count].key = key;
	entries[count].value = val;
	return (0);
}

static void	process_input_pairs(t_map **entries, int *capacity,
	int *count)
{
	while (1)
	{
		if (read_key_value_pair(*entries, *count) == -1)
			break ;
		(*count)++;
		if (*count >= *capacity)
			*entries = expand_entries(*entries, capacity, *count);
		if (!*entries)
			return ;
	}
}

void	parse_input(t_map **entries, int *size, int capacity, int count)
{
	*entries = malloc(capacity * sizeof(t_map));
	if (!*entries)
		return ;
	process_input_pairs(entries, &capacity, &count);
	if (count < capacity)
		*entries = shrink_entries(*entries, count);
	*size = count;
}
