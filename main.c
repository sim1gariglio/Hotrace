/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:31:05 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 17:18:44 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void ft_putstr(const char *str)
{
    if (str)
    {
        while (*str)
        {
            write(1, str, 1);
            str++;
        }
    }
}

void search_keywords(t_hashmap *hashmap)
{
    char *keyword;
    char *value;

    while ((keyword = fast_read_line()) != NULL)
    {
        if (keyword[0] == '\0')
        {
            free(keyword);
            break;
        }

        value = search_in_hashmap(hashmap, keyword);
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
    parse_input(&entries, &size);
    if (!entries)
        return (1);
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
    free(hashmap->array);
    free(hashmap);
    return (0);
}