/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_capacity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:10:36 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 17:08:58 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	handle_capacity(t_map **entries, t_map tmp, int count, int *capacity)
{
    if (count >= *capacity)
    {
        if (!resize_entries_array(entries, tmp, count, capacity))
            return (0);
    }
    return (1);
}

int	resize_entries_array(t_map **entries, t_map tmp, int count, int *capacity)
{
    int		i;
    t_map	*new_entries;

    i = 0;
    *capacity *= 2;  // Raddoppia la capacità
    new_entries = malloc(*capacity * sizeof(t_map));
    if (!new_entries)
    {
        // Libera la memoria già allocata
        free(tmp.key);
        free(tmp.value);
        while (i < count)
        {
            free((*entries)[i].key);
            free((*entries)[i].value);
            i++;
        }
        free(*entries);
        *entries = NULL;
        return (0);
    }
    
    // Copia i dati esistenti
    while (i < count)
    {
        new_entries[i].key = (*entries)[i].key;
        new_entries[i].value = (*entries)[i].value;
        i++;
    }
    
    // Libera il vecchio array e aggiorna il puntatore
    free(*entries);
    *entries = new_entries;
    return (1);
}

void	free_strings(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
