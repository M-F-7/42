/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:06:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 13:10:37 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	width_window(t_data *m)
{
	return (ft_strlen(m->map[0]));
}

int	height_window(t_data *m)
{
	int	i;

	i = 0;
	while (m->map[i])
		i++;
	return (i);
}

int	x_max(int x)
{
	return (x - 1);
}

int	y_max(int y)
{
	return (y - 1);
}
