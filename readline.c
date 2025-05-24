#include "hotrace.h"

static int	rl_reload_buffer(char *buffer, int *position, int *bytes_read)
{
    *bytes_read = read(0, buffer, BUFFER_SIZE);
    *position = 0;
    return *bytes_read;
}

static char	*rl_expand_line(char *line, int *capacity, int length)
{
    int		new_capacity;
    char	*new_line;
    int		i;

    new_capacity = (*capacity ? *capacity * 2 : 64);
    new_line = malloc(new_capacity);
    if (!new_line)
        return NULL;
    i = 0;
    while (i < length)
    {
        new_line[i] = line[i];
        i++;
    }
    free(line);
    *capacity = new_capacity;
    return new_line;
}

static char	*rl_finalize_line(char *line, int length)
{
    char *result;
    int i;

    result = malloc(length + 1);
    if (!result)
    {
        free(line);
        return NULL;
    }
    i = 0;
    while (i < length)
    {
        result[i] = line[i];
        i++;
    }
    result[length] = '\0';
    free(line);
    return result;
}

static int	rl_fill_line(char **line, int *length, int *capacity,
        char *buffer, int *position, int *bytes_read)
{
    char	c;

    while (1)
    {
        c = buffer[(*position)++];
        if (c == '\n')
            return (1); // Line complete
        if (*length >= *capacity)
        {
            *line = rl_expand_line(*line, capacity, *length);
            if (!*line)
                return (0); // Allocation failed
        }
        (*line)[(*length)++] = c;
        if (*position >= *bytes_read)
            return (2); // Buffer needs reload
    }
}

char	*fast_read_line(int capacity, int length)
{
    static char	buffer[BUFFER_SIZE];
    static int	position = 0;
    static int	bytes_read = 0;
    char		*line;
    int			status;

    line = NULL;
    if (position >= bytes_read)
    {
        if (rl_reload_buffer(buffer, &position, &bytes_read) <= 0)
            return (NULL);
    }
    while (1)
    {
        status = rl_fill_line(&line, &length, &capacity, buffer, &position, &bytes_read);
        if (status == 1)
            break;
        if (status == 0)
            return (NULL);
        if (status == 2)
        {
            if (rl_reload_buffer(buffer, &position, &bytes_read) <= 0)
                break;
        }
    }
    return (rl_finalize_line(line, length));
}