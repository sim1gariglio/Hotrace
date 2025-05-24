#include "hotrace.h"

int	nearest_power_of_2(int size)
{
    int	power = 1;

    while (power < size)
        power *= 2;
    return (power);
}

int	hash_function(const char *key, int size)
{
    unsigned long	hash = 0;
    int				c;

    while ((c = *key++))
        hash = hash * 31 + c;
    return (hash % size);
}

// Modificata per accettare un array di t_map invece di una lista
t_hashmap *create_hashmap(t_map *entries, int size)
{
    t_hashmap   *hashmap;
    int         hashmap_size;

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
    for (int i = 0; i < hashmap_size; i++)
    {
        hashmap->array[i].key = NULL;
        hashmap->array[i].value = NULL;
    }

    hashmap->size = hashmap_size;

    // Inserisci tutti gli elementi nell'hashmap
    for (int i = 0; i < size; i++)
    {
        int index = hash_function(entries[i].key, hashmap->size);

        // Gestisci le collisioni con linear probing
        while (hashmap->array[index].key != NULL)
            index = (index + 1) % hashmap->size;

        // Inserisci l'elemento nell'hashmap
        hashmap->array[index].key = entries[i].key;
        hashmap->array[index].value = entries[i].value;
    }

    return (hashmap);
}

// Create a hash map from the linked list
// t_hashmap	*create_hashmap(t_list *list, int size)
// {
//     t_hashmap	*hashmap;
//     int			hashmap_size;
//     t_list		*current;

//     hashmap_size = nearest_power_of_2((size * 10) / 7);
//     hashmap = malloc(sizeof(t_hashmap));
//     if (!hashmap)
//         return (NULL);
//     hashmap->array = malloc(sizeof(t_map) * hashmap_size);
//     if (!hashmap->array)
//     {
//         free(hashmap);
//         return (NULL);
//     }

//     for (int i = 0; i < hashmap_size; i++)
//     {
//         hashmap->array[i].key = NULL;
//         hashmap->array[i].value = NULL;
//     }

//     hashmap->size = hashmap_size;

//     current = list;
//     while (current)
//     {
//         int index = hash_function(current->key, hashmap->size);

//         // Handle collisions using linear probing
//         while (hashmap->array[index].key != NULL)
//             index = (index + 1) % hashmap->size;

//         hashmap->array[index].key = current->key;
//         hashmap->array[index].value = current->value;

//         current = current->next;
//     }

//     return (hashmap);
// }

char	*search_in_hashmap(t_hashmap *hashmap, const char *key)
{
    int		index;
    int		original_index;
    int		probes = 0;

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