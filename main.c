/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:55:11 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 18:55:13 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	ft_putstr(const char *s)
{
	if (!s)
		return ;
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

void	search_keywords(t_hashmap *hashmap)
{
	t_map	tmp;

	tmp.key = fast_read_line(0, 0, 0, 0);
	while (tmp.key != NULL)
	{
		if (tmp.key[0] == '\0')
		{
			free(tmp.key);
			break ;
		}
		tmp.value = search_in_hashmap(hashmap, tmp.key);
		if (tmp.value)
			ft_putstr(tmp.value);
		else
		{
			ft_putstr(tmp.key);
			ft_putstr(": Not found.\n");
		}
		free(tmp.key);
		tmp.key = fast_read_line(0, 0, 0, 0);
	}
}

void	free_hashmap(t_hashmap *hashmap)
{
	int	i;

	i = 0;
	if (!hashmap)
		return ;
	while (i < hashmap->size)
	{
		free(hashmap->array[i].key);
		free(hashmap->array[i].value);
		i++;
	}
	free(hashmap->array);
	free(hashmap);
}

void	free_map(t_map *entries, int size)
{
	int	i;

	i = 0;
	if (!entries)
		return ;
	while (i < size)
	{
		free(entries[i].key);
		free(entries[i].value);
		i++;
	}
	free(entries);
}

int	main(void)
{
	t_list		*list;
	t_hashmap	*hashmap;
	int			size;
	int			i;
	t_map		*entries;

	i = 0;
	size = 0;
	list = NULL;
	parse_input(&entries, &size, 1024, 0);
	hashmap = create_hashmap(entries, size);
	if (!hashmap)
	{
		free_map(entries, size);
		return (1);
	}
	free(entries);
	search_keywords(hashmap);
	free_hashmap(hashmap);
	return (0);
}
