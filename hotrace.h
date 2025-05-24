#ifndef HOTRACE_H
# define HOTRACE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# define BUFFER_SIZE 1024

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_map
{
	char	*key;
	char	*value;
}	t_map;

typedef struct s_hashmap
{
	t_map	*array;
	int		size;
}	t_hashmap;

char		*get_next_line(int fd);
char		*ft_read(char *old_str, int fd);
char		*ft_newstrjoin(char *old_str, char *buf);
char		*ft_correctline(char *old_str);
char		*ft_resto(char *old_str);
size_t		ft_strlen(char *str);
char		*ft_strchr(char *s, int c);
t_hashmap	*create_hashmap(t_map *entries, int size);
char		*search_in_hashmap(t_hashmap *hashmap, const char *key);
int			hash_function(const char *key, int size);
int			nearest_power_of_2(int size);
void		parse_input(t_map **entries, int *size);
char		*fast_read_line(void);

#endif
