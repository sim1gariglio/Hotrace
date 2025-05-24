# include "hotrace.h"

int main()
{
    char *line;
    long size = 0;

    while ((line = get_next_line(0)) != NULL)
    {
        printf("%s", line);
        free(line);
        size ++;
    }
    return (0);
}