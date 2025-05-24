/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashMap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 01:00:00 by sgarigli          #+#    #+#             */
/*   Updated: 2025/05/24 17:19:17 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	nearest_power_of_2(int size)
{
    int	power;

    power = 1;
    while (power < size)
        power *= 2;
    return (power);
}

int	hash_function(const char *key, int size)
{
    unsigned long	hash;
    int				c;

    hash = 0;
    while ((c = *key++))
        hash = hash * 31 + c;
    return (hash % size);
}

t_hashmap *create_hashmap(t_map *entries, int size)
{
    t_hashmap   *hashmap;
    int         hashmap_size;
    int         i;
    int         index;

    // Calcola la dimensione ottimale della tabella hash (70% di occupazione)
    hashmap_size = nearest_power_of_2((size * 10) / 7);
    
    // Alloca la struttura hashmap
    hashmap = malloc(sizeof(t_hashmap));
    if (!hashmap)
        return (NULL);
    
    // Alloca l'array della tabella hash
    hashmap->array = malloc(sizeof(t_map) * hashmap_size);
    if (!hashmap->array)
    {
        free(hashmap);
        return (NULL);
    }

    // Inizializza l'array con NULL
    i = 0;
    while (i < hashmap_size)
    {
        hashmap->array[i].key = NULL;
        hashmap->array[i].value = NULL;
        i++;
    }

    hashmap->size = hashmap_size;

    // Inserisci tutti gli elementi nell'hashmap
    i = 0;
    while (i < size)
    {
        index = hash_function(entries[i].key, hashmap->size);

        // Gestisci le collisioni con linear probing
        while (hashmap->array[index].key != NULL)
            index = (index + 1) % hashmap->size;

        // Inserisci l'elemento nell'hashmap
        hashmap->array[index].key = entries[i].key;
        hashmap->array[index].value = entries[i].value;
        i++;
    }

    return (hashmap);
}

char	*search_in_hashmap(t_hashmap *hashmap, const char *key)
{
    int		index;
    int		original_index;
    int		probes;

    probes = 0;
    index = hash_function(key, hashmap->size);
    original_index = index;

    while (hashmap->array[index].key != NULL)
    {
        if (ft_strcmp(hashmap->array[index].key, key) == 0)
            return (hashmap->array[index].value); // Key found

        index = (index + 1) % hashmap->size; // Linear probing
        probes++;

        if (index == original_index || probes >= hashmap->size)
            break;
    }

    return (NULL); // Key not found
}

void	init_and_fill_hashmap(t_hashmap *hashmap, t_map *entries,
                                int size, int hashmap_size)
{
    int	i;
    int	index;

    hashmap->array = malloc(sizeof(t_map) * hashmap_size);
    if (!hashmap->array)
    {
        free(hashmap); // Aggiungi questa riga per liberare hashmap in caso di errore
        return ;
    }
	i = 0;
	while (i < hashmap_size)
	{
		hashmap->array[i].key = NULL;
		hashmap->array[i].value = NULL;
		i++;
	}
	hashmap->size = hashmap_size;
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
