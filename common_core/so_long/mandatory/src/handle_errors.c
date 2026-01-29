/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:39:56 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 23:34:37 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_errors(t_data *m)
{
	if (!(check_map(m)))
	{
		free_tab(m->map);
		exit(EXIT_FAILURE);
	}
	else if (!(check_content(m)))
	{
		free_tab(m->map);
		exit(EXIT_FAILURE);
	}
	else if (!(check_double(m)))
	{
		free_tab(m->map);
		exit(EXIT_FAILURE);
	}
	else if (!(check_wall(m)) || !(check_valid_path(m)))
	{
		free_tab(m->map);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	check_file(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (0);
	}
	if (!(ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".ber", 4) == 0))
	{
		ft_putstr_fd("Bad extension for the map\n", 2);
		return (0);
	}
	return (1);
}

int	check_map(t_data *m)
{
	size_t	len;
	int		i;

	if (!m->map || !m->map[0])
		return (0);
	len = ft_strlen(m->map[0]);
	i = 1;
	while (m->map[i])
	{
		if (ft_strlen(m->map[i]) != len)
			return (ft_putstr_fd("Not same width of line\n", 2), 0);
		i++;
	}
	return (1);
}

int	check_content(t_data *m)
{
	static int	y = -1;
	int			x;
	static int	exit = 0;
	static int	coll = 0;
	static int	player = 0;

	while (m->map[++y])
	{
		x = 0;
		while (m->map[y][x])
		{
			if (m->map[y][x] == 'P')
				player++;
			else if (m->map[y][x] == 'C')
				coll++;
			else if (m->map[y][x] == 'E')
				exit++;
			else if (m->map[y][x] != '0' && m->map[y][x] != '1')
				return (ft_putstr_fd("Problem with case type in map\n", 2), 0);
			x++;
		}
	}
	if (player != 1 || exit < 1 || coll < 1)
		return (ft_putstr_fd("Problem with the number of case type\n", 2), 0);
	return (1);
}

int	check_double(t_data *m)
{
	int	i;
	int	j;
	int	count_exit;
	int	count_player;

	j = 0;
	count_exit = 0;
	count_player = 0;
	while (m->map[j])
	{
		i = 0;
		while (m->map[j][i])
		{
			if (m->map[j][i] == 'P')
				count_player++;
			else if (m->map[j][i] == 'E')
				count_exit++;
			i++;
		}
		j++;
	}
	if (count_exit != 1 || count_player != 1)
		return (ft_putstr_fd("Too many players or exit in the map\n", 2), 0);
	return (1);
}
