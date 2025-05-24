#include "hotrace.h"

char *fast_read_line(int capacity, int length) 
{
    static char buffer[BUFFER_SIZE];
    static int position = 0;
    static int bytes_read = 0;
    char *line = NULL;
    
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