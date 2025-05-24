#include "hotrace.h"

// Transfer data from the linked list to the hash map
void	list_to_hashmap(t_map *list, t_map **map, int size)
{
    *map = malloc(sizeof(t_map) * size);
    if (!*map)
        return;

    for (int i = 0; i < size; i++)
    {
        (*map)[i].key = list->key;
        (*map)[i].value = list->value;
        (*map)[i].next = NULL;
        list = list->next;
    }
}