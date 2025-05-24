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

void search_keywords(t_hashmap *hashmap)
{
    char *keyword;

    while ((keyword = fast_read_line()) != NULL)
    {
        if (keyword[0] == '\0')
        {
            free(keyword);
            break;
        }

        char *value = search_in_hashmap(hashmap, keyword);
        if (value)
            printf("%s\n", value);
        else
            printf("%s: Not found.\n", keyword);

        free(keyword);
    }
}

// void	search_keywords(t_hashmap *hashmap)
// {
// 	char *keyword;

// 	while ((keyword = get_next_line(0)) != NULL)
// 	{
// 		if (keyword[0] == '\n')
// 		{
// 			free(keyword);
// 			break;
// 		}

// 		char *value = search_in_hashmap(hashmap, keyword);
// 		if (value)
// 			printf("%s", value);
// 		else
// 			printf("%s: Not found.\n", keyword); // Print "Not found" if the keyword is missing

// 		free(keyword);
// 	}
// }

int	main(void)
{
	t_list		*list;
	//t_map		*map;
	t_hashmap	*hashmap;
	int			size;
	int			i;

	t_map	*entries;

	i = 0;
	size = 0;
	list = NULL;
	// Step 1: Parse input into a linked list and get the size
	parse_input(&entries, &size);

	// // Step 2: Create the hash map
	// hashmap = create_hashmap(list, size);
	hashmap = create_hashmap(entries, size);
    if (!hashmap) {
        // Libera la memoria e gestisci l'errore
        for (int i = 0; i < size; i++) {
            free(entries[i].key);
            free(entries[i].value);
        }
        free(entries);
        return 1;
    }

    // Non hai più bisogno dell'array entries dopo aver creato l'hashmap
    // perché le chiavi e i valori sono stati trasferiti all'hashmap
    free(entries);

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