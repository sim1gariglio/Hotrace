/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseInput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:35:58 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 15:58:37 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	parse_input(t_map **entries, int *size, int capacity)
{
	int		count;
	t_map	tmp;

	count = 0;
	*entries = malloc(capacity * sizeof(t_map));
	if (!*entries)
		return ;
	while (1)
	{
		tmp.key = fast_read_line(0, 0, NULL, 0);
		if (!is_valid_keyword(tmp.key))
			break ;
		tmp.value = fast_read_line(0, 0, NULL, 0);
		if (!is_valid_value(tmp.value, tmp.key))
			break ;
		if (!handle_capacity(entries, tmp, count, &capacity))
			return ;
		(*entries)[count].key = tmp.key;
		(*entries)[count].value = tmp.value;
		count++;
	}
	*size = count;
}

int	is_valid_keyword(char *keyword)
{
	if (!keyword || keyword[0] == '\0')
	{
		free(keyword);
		return (0);
	}
	return (1);
}

int	is_valid_value(char *value, char *keyword)
{
	if (!value)
	{
		free(keyword);
		return (0);
	}
	return (1);
}
