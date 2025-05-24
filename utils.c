/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:55:21 by mruggier          #+#    #+#             */
/*   Updated: 2025/05/24 19:00:03 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	nearest_power_of_2(int size)
{
	int	power;

	power = 1;
	while (power < size)
		power *= 2;
	return (power);
}

int	rl_reload_buffer(char *buffer, int *position, int *bytes_read)
{
	*bytes_read = read(0, buffer, BUFFER_SIZE);
	*position = 0;
	return (*bytes_read);
}
