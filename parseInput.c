/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseInput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:35:58 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 17:18:30 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void parse_input(t_map **entries, int *size)
{
    int capacity = 1024;  // Inizia con una capacità ragionevole
    int count = 0;
    
    // Alloca l'array iniziale
    *entries = malloc(capacity * sizeof(t_map));
    if (!*entries)
        return;
    
    // Leggi e rialloca all'occorrenza
    while (1) {
        char *keyword = fast_read_line();
        if (!keyword || keyword[0] == '\0') {
            free(keyword);
            break;
        }
        
        char *value = fast_read_line();
        if (!value) {
            free(keyword);
            break;
        }
        
        // Espandi l'array se necessario
        if (count >= capacity) {
            capacity *= 2;
            t_map *new_entries = malloc(capacity * sizeof(t_map));
            if (!new_entries) {
                // Gestisci l'errore
                free(keyword);
                free(value);
                
                for (int i = 0; i < count; i++) {
                    free((*entries)[i].key);
                    free((*entries)[i].value);
                }
                free(*entries);
                *entries = NULL;
                return;
            }
            
            // Copia i dati esistenti
            for (int i = 0; i < count; i++) {
                new_entries[i].key = (*entries)[i].key;
                new_entries[i].value = (*entries)[i].value;
            }
            
            free(*entries);
            *entries = new_entries;
        }
        
        // Aggiungi la nuova entry
        (*entries)[count].key = keyword;
        (*entries)[count].value = value;
        count++;
    }
    
    *size = count;
}

int	is_valid_keyword(char *keyword)
{
    if (!keyword || keyword[0] == '\0')
    {
        free(keyword);
        return (0);
    }
    return (1);
}

int	is_valid_value(char *value, char *keyword)
{
    if (!value)
    {
        free(keyword);
        return (0);
    }
    return (1);
}