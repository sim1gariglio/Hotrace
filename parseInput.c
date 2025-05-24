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

// Parse input and populate the linked list
void	parse_input(t_list **list, int *size)
{
    char	*keyword;
    char	*value;

    *size = 0; // Initialize the size counter

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