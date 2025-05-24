/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashMap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:55:07 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 18:55:10 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	hash_function(const char *key, int size)
{
	unsigned long	hash;
	int				c;

	hash = 0;
	while (*key)
	{
		c = *key++;
		hash = hash * 31 + c;
	}
	return (hash % size);
}

static void	init_hashmap_entries(t_hashmap *hashmap, int hashmap_size)
{
	int	i;

	i = 0;
	while (i < hashmap_size)
	{
		hashmap->array[i].key = NULL;
		hashmap->array[i].value = NULL;
		i++;
	}
	hashmap->size = hashmap_size;
}

static void	populate_hashmap(t_hashmap *hashmap, t_map *entries, int size)
{
	int	index;
	int	i;

	i = 0;
	while (i < size)
	{
		index = hash_function(entries[i].key, hashmap->size);
		while (hashmap->array[index].key != NULL)
			index = (index + 1) % hashmap->size;
		hashmap->array[index].key = entries[i].key;
		hashmap->array[index].value = entries[i].value;
		i++;
	}
}

t_hashmap	*create_hashmap(t_map *entries, int size)
{
	t_hashmap	*hashmap;
	int			hashmap_size;

	hashmap_size = nearest_power_of_2((size * 10) / 7);
	hashmap = malloc(sizeof(t_hashmap));
	if (!hashmap)
		return (NULL);
	hashmap->array = malloc(sizeof(t_map) * hashmap_size);
	if (!hashmap->array)
	{
		free(hashmap);
		return (NULL);
	}
	init_hashmap_entries(hashmap, hashmap_size);
	populate_hashmap(hashmap, entries, size);
	return (hashmap);
}

char	*search_in_hashmap(t_hashmap *hashmap, const char *key)
{
	int	index;
	int	original_index;
	int	probes;

	probes = 0;
	index = hash_function(key, hashmap->size);
	original_index = index;
	while (hashmap->array[index].key != NULL)
	{
		if (ft_strcmp(hashmap->array[index].key, key) == 0)
			return (hashmap->array[index].value);
		index = (index + 1) % hashmap->size;
		probes++;
		if (index == original_index || probes >= hashmap->size)
			break ;
	}
	return (NULL);
}
