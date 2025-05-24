#include "hotrace.h"

// Add a new node to the linked list and update the size
void	add_to_list(t_map **list, char *keyword, char *value, int *size)
{
    t_map	*new_node;
    t_map	*current;

    new_node = malloc(sizeof(t_map));
    if (!new_node)
        return;
    new_node->key = keyword;
    new_node->value = value;
    new_node->next = NULL;

    if (*list == NULL)
        *list = new_node;
    else
    {
        current = *list;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }

    (*size)++;
}

// Parse input and populate the linked list
void	parse_input(t_map **list, int *size)
{
    char	*keyword;
    char	*value;

    while (1)
    {
        keyword = get_next_line(0);
        if (!keyword || keyword[0] == '\n')
        {
            free(keyword);
            break;
        }

        value = get_next_line(0);
        if (!value || value[0] == '\n')
        {
            free(keyword);
            free(value);
            break;
        }

        add_to_list(list, keyword, value, size);
    }
}