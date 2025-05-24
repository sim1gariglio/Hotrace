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

void	parse_input(t_map **entries, int *size, int capacity, int count)
{
	char	*key;
	char	*val;

	*entries = malloc(capacity * sizeof(t_map));
	if (!*entries)
		return ;
	while (1)
	{
		key = fast_read_line(0, 0, 0, 0);
		if (!key || key[0] == '\0')
		{
			free(key);
			break ;
		}
		val = fast_read_line(0, 0, 0, 0);
		if (!val)
		{
			free(key);
			break ;
		}
		if (count >= capacity)
			*entries = expand_entries(*entries, &capacity, count);
		(*entries)[count].key = key;
		(*entries)[count].value = val;
		count++;
	}
	if (count < capacity)
		*entries = shrink_entries(*entries, count);
	*size = count;
}
