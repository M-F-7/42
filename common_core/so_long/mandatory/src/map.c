/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:24:46 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 13:13:57 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	map_fill(char **map)
{
	int	x;
	int	y;

	y = 0;
	if (!check_char(map))
		return ;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			ft_putchar_fd(map[y][x], 1);
			x++;
		}
		ft_putchar_fd('\n', 1);
		y++;
	}
}

int	nb_lines(int file)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(file);
		if (!line)
			return (count);
		count++;
		free(line);
	}
	return (count);
}

int	check_char(char **tab)
{
	int	i;
	int	j;

	j = 0;
	while (tab[j])
	{
		i = 0;
		while (tab[j][i])
		{
			if (tab[j][i] == '0')
				i++;
			else if (tab[j][i] == '1')
				i++;
			else if (tab[j][i] == 'P')
				i++;
			else if (tab[j][i] == 'E')
				i++;
			else if (tab[j][i] == 'C')
				i++;
			else
				return (0);
		}
		j++;
	}
	return (1);
}

void	map_draw(char **map, t_data *m, t_sprites *sprites)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			put_floor(m, sprites, x, y);
			if (map[y][x] == '1')
				put_wall(m, sprites, x, y);
			else if (map[y][x] == 'P')
				put_player(m, &m->game, x, y);
			else if (map[y][x] == 'C')
				put_collectible(m, sprites, x, y);
			else if (map[y][x] == 'E')
				put_exit(m, sprites, x, y);
			x++;
		}
		y++;
	}
}
