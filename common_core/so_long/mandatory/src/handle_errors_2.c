/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:16:11 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 14:11:12 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_wall(t_data *m)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = 0;
	j = 0;
	height = 0;
	if (!m->map || !m->map[0])
		return (0);
	width = ft_strlen(m->map[0]);
	while (m->map[height])
		height++;
	i = 0;
	while (i < width)
	{
		if (m->map[0][i] != '1' || m->map[height - 1][i] != '1')
			return (0);
		i++;
	}
	j = -1;
	while (++j < height)
		if (m->map[j][0] != '1' || m->map[j][width - 1] != '1')
			return (0);
	return (1);
}

static void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	if (map[y + 1][x])
		flood_fill(map, y + 1, x);
	if (y > 0 && map[y - 1][x])
		flood_fill(map, y - 1, x);
	if (map[y][x + 1])
		flood_fill(map, y, x + 1);
	if (x > 0 && map[y][x - 1])
		flood_fill(map, y, x - 1);
}

static char	**dup_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	i = 0;
	if (!copy)
		return (NULL);
	while (i < height)
	{
		copy[i] = strdup(map[i]);
		if (!copy[i++])
			return (free_tab(copy), NULL);
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_print_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
	ft_putstr_fd("Player cant reach the exit\n", 2);
}

int	check_valid_path(t_data *m)
{
	int		i;
	int		j;
	int		height;
	int		width;
	char	**map_copy;

	j = -1;
	height = height_window(m);
	width = ft_strlen(m->map[0]);
	map_copy = dup_map(m->map, height);
	if (!map_copy)
		return (0);
	find_player_pos(m);
	flood_fill(map_copy, m->game.player_y, m->game.player_x);
	while (++j < height)
	{
		i = -1;
		while (++i < width)
			if (map_copy[j][i] == 'C' || map_copy[j][i] == 'E')
				return (free_print_tab(map_copy), 0);
	}
	return (free_tab(map_copy), 1);
}
