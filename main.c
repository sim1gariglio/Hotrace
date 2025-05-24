#include "hotrace.h"

int	main(void)
{
	char	*line;
	long	size;

	size = 0;
	line = get_next_line(0);
	if (line == NULL)
	{
		printf("Error\n");
		return (1);
	}
	while ((line) != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(0);
		size ++;
	}
	return (0);
}
