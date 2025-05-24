#include "hotrace.h"

// Add a new node to the linked list
void	add_to_list(t_list **list, char *keyword, char *value, int *size)
{
    t_list	*new_node;
    t_list	*current;

    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return;
    new_node->key = keyword;
    new_node->value = value;
    new_node->next = NULL;

    if (*list == NULL)
        *list = new_node; // First node in the list
    else
    {
        current = *list;
        while (current->next)
            current = current->next;
        current->next = new_node; // Append to the end of the list
    }

    (*size)++; // Increment the size counter
}

//  Parse input and populate the linked list
// void	parse_input(t_list **list, int *size)
// {
//     char	*keyword;
//     char	*value;

//     *size = 0; // Initialize the size counter

//     while (1)
//     {
//         keyword = get_next_line(0);
//         if (!keyword || keyword[0] == '\n')
//         {
//             free(keyword);
//             break;
//         }

//         value = get_next_line(0);
//         if (!value || value[0] == '\n')
//         {
//             free(keyword);
//             free(value);
//             break;
//         }

//         add_to_list(list, keyword, value, size);
//     }
// }

// In un file appropriato (ad es. parsing.c)
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