/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:27:46 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 22:36:04 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	destroy_barrels(t_data *m, t_sprites *sprites)
{
	if (sprites->wallbluebottom)
		mlx_destroy_image(m->mlx, sprites->barrels);
}

void	destroy_all(t_data *m, t_sprites *sprites)
{
	if (sprites)
	{
		destroy_player(m, sprites);
		destroy_other(m, sprites);
		destroy_barrels(m, sprites);
	}
	if (m->window && m->mlx)
		mlx_destroy_window(m->mlx, m->window);
	if (m->mlx)
		mlx_destroy_display(m->mlx);
}

void	destroy_player(t_data *m, t_sprites *sprites)
{
	if (sprites->playerbottomleft)
		mlx_destroy_image(m->mlx, sprites->playerbottomleft);
	if (sprites->playerbottommid)
		mlx_destroy_image(m->mlx, sprites->playerbottommid);
	if (sprites->playerbottomright)
		mlx_destroy_image(m->mlx, sprites->playerbottomright);
	if (sprites->playerleftleft)
		mlx_destroy_image(m->mlx, sprites->playerleftleft);
	if (sprites->playerleftmid)
		mlx_destroy_image(m->mlx, sprites->playerleftmid);
	if (sprites->playerleftright)
		mlx_destroy_image(m->mlx, sprites->playerleftright);
	if (sprites->playerrightleft)
		mlx_destroy_image(m->mlx, sprites->playerrightleft);
	if (sprites->playerrightmid)
		mlx_destroy_image(m->mlx, sprites->playerrightmid);
	if (sprites->playerrightright)
		mlx_destroy_image(m->mlx, sprites->playerrightright);
	if (sprites->playertopright)
		mlx_destroy_image(m->mlx, sprites->playertopright);
	if (sprites->playertopmid)
		mlx_destroy_image(m->mlx, sprites->playertopmid);
	if (sprites->playertopleft)
		mlx_destroy_image(m->mlx, sprites->playertopleft);
}

void	destroy_other(t_data *m, t_sprites *sprites)
{
	if (sprites->wallbluebottom)
		mlx_destroy_image(m->mlx, sprites->wallbluebottom);
	if (sprites->wallblueleft)
		mlx_destroy_image(m->mlx, sprites->wallblueleft);
	if (sprites->wallblueright)
		mlx_destroy_image(m->mlx, sprites->wallblueright);
	if (sprites->wallbluetop)
		mlx_destroy_image(m->mlx, sprites->wallbluetop);
	if (sprites->wallwhitebottom)
		mlx_destroy_image(m->mlx, sprites->wallwhitebottom);
	if (sprites->wallwhiteleft)
		mlx_destroy_image(m->mlx, sprites->wallwhiteleft);
	if (sprites->wallwhiteright)
		mlx_destroy_image(m->mlx, sprites->wallwhiteright);
	if (sprites->wallwhitetop)
		mlx_destroy_image(m->mlx, sprites->wallwhitetop);
	if (sprites->floorblue)
		mlx_destroy_image(m->mlx, sprites->floorblue);
	if (sprites->floorwhite)
		mlx_destroy_image(m->mlx, sprites->floorwhite);
	if (sprites->cheese)
		mlx_destroy_image(m->mlx, sprites->cheese);
	if (sprites->exit)
		mlx_destroy_image(m->mlx, sprites->exit);
}
