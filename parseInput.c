#include "hotrace.h"

void parse_input(t_map **entries, int *size, int capacity, int count)
{
    // Alloca l'array iniziale
    *entries = malloc(capacity * sizeof(t_map));
    if (!*entries)
        return;
    
    // Leggi e rialloca all'occorrenza
    while (1) {
        char *keyword = fast_read_line(0, 0, 0, 0);
        if (!keyword || keyword[0] == '\0') {
            free(keyword);
            break;
        }
        
        char *value = fast_read_line(0, 0, 0, 0);
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
    
    // Ridimensiona alla dimensione esatta se necessario
    if (count < capacity) {
        t_map *final_entries = malloc(count * sizeof(t_map));
        if (final_entries) {
            for (int i = 0; i < count; i++) {
                final_entries[i].key = (*entries)[i].key;
                final_entries[i].value = (*entries)[i].value;
            }
            free(*entries);
            *entries = final_entries;
        }
    }
    
    *size = count;
}