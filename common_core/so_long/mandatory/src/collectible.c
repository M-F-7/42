/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:16:41 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 12:43:54 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	count_collect(t_data *m)
{
	int	i;
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (m->map[j])
	{
		i = 0;
		while (m->map[j][i])
		{
			if (m->map[j][i] == 'C')
				count++;
			i++;
		}
		j++;
	}
	return (count);
}

int	collect(t_data *m)
{
	int	max_count;

	max_count = count_collect(m);
	if (m->game.collected != max_count)
		return (0);
	return (1);
}
