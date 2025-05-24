/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli < sgarigli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 01:00:00 by sgarigli          #+#    #+#             */
/*   Updated: 2024/05/24 16:31:02 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_hashmap *create_hashmap(t_map *entries, int size);
char	*search_in_hashmap(t_hashmap *hashmap, const char *key);
int		hash_function(const char *key, int size);
int		nearest_power_of_2(int size);
int		ft_strcmp(const char *s1, const char *s2);
void    parse_input(t_map **entries, int *size, int capacity);
char	*fast_read_line(void); 

// =======
// int			ft_strcmp(const char *s1, const char *s2);
// void		init_and_fill_hashmap(t_hashmap *hashmap, t_map *entries,
// 				int size, int hashmap_size);
// t_hashmap	*create_hashmap(t_map *entries, int size);
// char		*search_in_hashmap(t_hashmap *hashmap, const char *key);
// int			hash_function(const char *key, int size);
// int			nearest_power_of_2(int size);
// void		parse_input(t_map **entries, int *size);
// char		*fast_read_line(void);
// >>>>>>> norminetting


#endif
