#include "hotrace.h"

void	print_hashmap(t_hashmap *hashmap)
{
	int i;

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
	char *keyword;

	while ((keyword = get_next_line(0)) != NULL)
	{
		if (keyword[0] == '\n')
		{
			free(keyword);
			break;
		}

		char *value = search_in_hashmap(hashmap, keyword);
		if (value)
			printf("%s", value);
		else
			printf("%s: Not found.\n", keyword); // Print "Not found" if the keyword is missing

		free(keyword);
	}
}

int	main(void)
{
	t_list		*list;
	t_hashmap	*hashmap;
	int			size;
	int			i;

	i = 0;
	size = 0;
	list = NULL;
	// Step 1: Parse input into a linked list and get the size
	parse_input(&list, &size);

	// Step 2: Create the hash map
	hashmap = create_hashmap(list, size);

	// Step 3: Print the hash map for testing
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
	free(hashmap->array);
	free(hashmap);

	return (0);
}