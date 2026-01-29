/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:02:41 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 23:26:27 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	update_map(t_data *m, int x, int y)
{
	if (m->game.player_x != x || m->game.player_y != y)
	{
		m->game.steps++;
		ft_printf("Steps: %d\n", m->game.steps);
	}
	if (m->map[m->game.player_y][m->game.player_x] == 'C')
		m->game.collected++;
	if (m->map[m->game.player_y][m->game.player_x] == 'E')
	{
		if (m->game.collected == m->game.total_collectibles)
			close_window(m);
		return (0);
	}
	m->map[y][x] = '0';
	m->map[m->game.player_y][m->game.player_x] = 'P';
	m->game.player_anim_frame = (m->game.player_anim_frame + 1) % 3;
	map_draw(m->map, m, &m->sprites);
	return (0);
}

int	key_info(int keycode, t_data *m)
{
	int	x;
	int	y;

	find_player_pos(m);
	x = m->game.player_x;
	y = m->game.player_y;
	if (keycode == 65307)
		close_window(m);
	else if (keycode == 97)
		player_left(m);
	else if (keycode == 119)
		player_forward(m);
	else if (keycode == 115)
		player_back(m);
	else if (keycode == 100)
		player_right(m);
	else
		return (0);
	if (m->map[y][x] == '1')
		return (0);
	update_map(m, x, y);
	return (0);
}

int	close_window(t_data *m)
{
	destroy_all(m, &m->sprites);
	free_all(m);
	exit(EXIT_SUCCESS);
	return (0);
}

void	display_steps(t_data *m)
{
	char	*steps_str;

	steps_str = ft_itoa(m->game.steps);
	if (steps_str)
	{
		mlx_string_put(m->mlx, m->window, 10, 10, 000000, "Steps:");
		mlx_string_put(m->mlx, m->window, 70, 10, 000000, steps_str);
		free(steps_str);
	}
}

void	free_all(t_data *m)
{
	if (m->map)
		free_tab(m->map);
	if (m->mlx)
		free(m->mlx);
}
