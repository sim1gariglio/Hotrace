/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:10:25 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 17:18:05 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

char *fast_read_line(void) 
{
    static char buffer[BUFFER_SIZE];
    static int position = 0;
    static int bytes_read = 0;
    
    char *line = NULL;
    int capacity = 0;
    int length = 0;
    
    // Ricarica il buffer se necessario
    if (position >= bytes_read) {
        bytes_read = read(0, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            return NULL;
        position = 0;
    }
    
    // Continua a leggere fino a newline o EOF
    while (1) {
        char c = buffer[position++];
        
        if (c == '\n')
            break;
            
        // Espandi il buffer se necessario
        if (length >= capacity) {
            capacity = capacity ? capacity * 2 : 64;
            char *new_line = malloc(capacity);
            if (!new_line) {
                free(line);
                return NULL;
            }
            
            for (int i = 0; i < length; i++)
                new_line[i] = line[i];
                
            free(line);
            line = new_line;
        }
        
        line[length++] = c;
        
        // Ricarica il buffer se necessario
        if (position >= bytes_read) {
            bytes_read = read(0, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
            position = 0;
        }
    }
    
    // Alloca il risultato finale della dimensione esatta
    char *result = malloc(length + 1);
    if (!result) {
        free(line);
        return NULL;
    }
    
    for (int i = 0; i < length; i++)
        result[i] = line[i];
    result[length] = '\0';
    
    free(line);
    return result;
}

int	refill_buffer(char buffer[BUFFER_SIZE], int *position, int *bytes_read)
{
	*bytes_read = read(0, buffer, BUFFER_SIZE);
	if (*bytes_read <= 0)
		return (0);
	*position = 0;
	return (1);
}

int	expand_buffer(char **line, int *capacity, int length)
{
	char	*new_line;
	int		i;

	if (*capacity <= 0)
		*capacity = 64;
	else
		*capacity *= 2;
	new_line = malloc(*capacity);
	if (!new_line)
	{
		free (*line);
		return (0);
	}
	i = 0;
	while (i < length)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	free (*line);
	*line = new_line;
	return (1);
}

int	process_char(char **line, int *length, int *capacity)
{
    static char	buffer[BUFFER_SIZE];
    static int	position = 0; // Inizializza esplicitamente
    static int	bytes_read = 0; // Inizializza esplicitamente
    char		c;

    if (position >= bytes_read)
    {
        if (!refill_buffer(buffer, &position, &bytes_read))
            return (0); // Usa la funzione refill_buffer per maggiore chiarezza
    }
    c = buffer[position++];
    if (c == '\n')
        return (2);
    // Se la capacità è 0 o line non è stato ancora allocato,
    // dobbiamo fare un'inizializzazione
    if (*capacity <= 0 || !(*line))
    {
        *capacity = 64; // Inizializza con dimensione ragionevole
        *line = malloc(*capacity);
        if (!(*line))
            return (-1);
    }
    else if (*length >= *capacity)
    {
        // Espandi il buffer se necessario
        if (!expand_buffer(line, capacity, *length))
            return (-1);
    }
    (*line)[(*length)++] = c;
    return (1);
}
