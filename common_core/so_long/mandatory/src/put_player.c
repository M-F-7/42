/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:31:59 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 14:31:47 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	put_bottom(t_data *m, t_game *game, int x, int y)
{
	if (!m->sprites.playerbottomleft || !m->sprites.playerbottommid
		|| !m->sprites.playerbottomright)
		return ;
	if (game->player_anim_frame == 0)
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerbottomleft,
			x * TILE, y * TILE);
	else if (game->player_anim_frame == 1)
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerbottommid, x
			* TILE, y * TILE);
	else
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerbottomright,
			x * TILE, y * TILE);
}

static void	put_left(t_data *m, t_game *game, int x, int y)
{
	if (!m->sprites.playerleftleft || !m->sprites.playerleftmid
		|| !m->sprites.playerleftright)
		return ;
	if (game->player_anim_frame == 0)
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerleftleft, x
			* TILE, y * TILE);
	else if (game->player_anim_frame == 1)
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerleftmid, x
			* TILE, y * TILE);
	else
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerleftright, x
			* TILE, y * TILE);
}

static void	put_right(t_data *m, t_game *game, int x, int y)
{
	if (!m->sprites.playerrightleft || !m->sprites.playerrightmid
		|| !m->sprites.playerrightright)
		return ;
	if (game->player_anim_frame == 0)
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerrightleft, x
			* TILE, y * TILE);
	else if (game->player_anim_frame == 1)
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerrightmid, x
			* TILE, y * TILE);
	else
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playerrightright,
			x * TILE, y * TILE);
}

static void	put_top(t_data *m, t_game *game, int x, int y)
{
	if (!m->sprites.playertopleft || !m->sprites.playertopmid
		|| !m->sprites.playertopright)
		return ;
	if (game->player_anim_frame == 0)
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playertopleft, x
			* TILE, y * TILE);
	else if (game->player_anim_frame == 1)
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playertopmid, x
			* TILE, y * TILE);
	else
		mlx_put_image_to_window(m->mlx, m->window, m->sprites.playertopright, x
			* TILE, y * TILE);
}

void	put_player(t_data *m, t_game *game, int x, int y)
{
	if (game->player_dir == 0)
		put_bottom(m, game, x, y);
	else if (game->player_dir == 1)
		put_left(m, game, x, y);
	else if (game->player_dir == 2)
		put_right(m, game, x, y);
	else if (game->player_dir == 3)
		put_top(m, game, x, y);
	display_steps(m);
}
