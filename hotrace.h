#ifndef HOTRACE_H
# define HOTRACE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# define BUFFER_SIZE 1

typedef struct s_map
{
	char			*key;
	char			*value;
	struct s_map	*next;
}	t_map;
;

char	*get_next_line(int fd);
char	*ft_read(char *old_str, int fd);
char	*ft_newstrjoin(char *old_str, char *buf);
char	*ft_correctline(char *old_str);
char	*ft_resto(char *old_str);
size_t	ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
void	add_to_list(t_map **list, char *keyword, char *value, int *size);
int		list_size(t_map *list);
void	parse_input(t_map **list, int *size);
void	list_to_hashmap(t_map *list, t_map **map, int size);

#endif
