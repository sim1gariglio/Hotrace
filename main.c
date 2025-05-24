#include "hotrace.h"

// void	print_hashmap(t_hashmap *hashmap)
// {
// 	int i;

// 	i = 0;
// 	while (i < hashmap->size)
// 	{
// 		if (hashmap->array[i].key)
// 		{
// 			printf("Keyword: %s\n", hashmap->array[i].key);
// 			printf("Value: %s\n", hashmap->array[i].value);
// 		}
// 		i++;
// 	}
// }

void	ft_putstr(const char *s)
{
    if (!s)
        return;
    while (*s)
        write(1, s++, 1);
}

void search_keywords(t_hashmap *hashmap)
{
    char *keyword;

    while ((keyword = fast_read_line(0, 0)) != NULL)
    {
        if (keyword[0] == '\0')
        {
            free(keyword);
            break;
        }

        char *value = search_in_hashmap(hashmap, keyword);
		if (value)
			ft_putstr(value);
		else
		{
			ft_putstr(keyword);
			ft_putstr(": Not found.\n");
		}
        free(keyword);
    }
}

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
	parse_input(&entries, &size);
	hashmap = create_hashmap(entries, size);
    if (!hashmap) {
        for (int i = 0; i < size; i++) {
            free(entries[i].key);
            free(entries[i].value);
        }
        free(entries);
        return 1;
    }
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
	free(hashmap->array);
	free(hashmap);
	return (0);
}