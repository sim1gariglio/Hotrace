#include "hotrace.h"

void	print_map(t_map *map, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		printf("Keyword: %s\n", map[i].key);
		printf("Value: %s\n", map[i].value);
		i++;
	}
}

int	main(void)
{
    t_map	*list;
    t_map	*map;
	int 	i;
	int		size;

	list = NULL;
	map = NULL;
	size = 0;
	i = 0;

    // Step 1: Parse input into a linked list and get the size
    parse_input(&list, &size);

    // Step 2: Transfer data to the hash map
    list_to_hashmap(list, &map, size);

    // Step 3: Print the hash map for testing
    print_map(map, size);

    // Free the allocated memory
    while (i < size)
	{
		free(map[i].key);
		free(map[i].value);
		i++;
	}
    return (0);
}