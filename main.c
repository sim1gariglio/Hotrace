/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:31:05 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 15:54:31 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	print_hashmap(t_hashmap *hashmap)
{
	int	i;

	i = 0;
	while (i < hashmap->size)
	{
		if (hashmap->array[i].key)
		{
			printf("Keyword: %s\n", hashmap->array[i].key);
			printf("Value: %s\n", hashmap->array[i].value);
		}
		i++;
	}
}

void	search_keywords(t_hashmap *hashmap)
{
	char	*keyword;
	char	*value;

	keyword = fast_read_line(0,0, NULL, 0);
	while (keyword != NULL)
	{
		if (keyword[0] == '\0')
		{
			free(keyword);
			break ;
		}
		value = search_in_hashmap(hashmap, keyword);
		if (value)
			printf("%s", value);
		else
			printf("%s: Not found.\n", keyword);
		free(keyword);
	}
}

int	i_am_free(t_map *entries, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(entries[i].key);
		free(entries[i].value);
		i++;
	}
	free(entries);
	return (1);
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
	parse_input(&entries, &size, 1024);
	hashmap = create_hashmap(entries, size);
	if (!hashmap)
		return (i_am_free(entries, size));
	free(entries);
	search_keywords(hashmap);
	while (i < hashmap->size)
	{
		if (hashmap->array[i].key)
		{
			free(hashmap->array[i].key);
			free(hashmap->array[i].value);
		}
		i++;
	}
	return (free(hashmap->array), free(hashmap), 0);
}
