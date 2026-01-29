/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:31:46 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 13:11:38 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	put_top(t_data *mlx, t_sprites *sprites, int x, int y)
{
	if ((x + y) % 2 == 0)
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->wallbluetop, x
			* TILE, y * TILE);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->wallwhitetop, x
			* TILE, y * TILE);
}

static void	put_bottom(t_data *mlx, t_sprites *sprites, int x, int y)
{
	if ((x + y) % 2 == 0)
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->wallbluebottom,
			x * TILE, y * TILE);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->wallwhitebottom,
			x * TILE, y * TILE);
}

static void	put_left(t_data *mlx, t_sprites *sprites, int x, int y)
{
	if ((x + y) % 2 == 0)
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->wallblueleft, x
			* TILE, y * TILE);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->wallwhiteleft, x
			* TILE, y * TILE);
}

static void	put_right(t_data *mlx, t_sprites *sprites, int x, int y)
{
	if ((x + y) % 2 == 0)
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->wallblueright, x
			* TILE, y * TILE);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->wallwhiteright,
			x * TILE, y * TILE);
}

void	put_wall(t_data *mlx, t_sprites *sprites, int x, int y)
{
	if (y == 0)
		put_top(mlx, sprites, x, y);
	else if (y == y_max(height_window(mlx)))
		put_bottom(mlx, sprites, x, y);
	else if (x == 0 && y != 0 && y != y_max(height_window(mlx)))
		put_left(mlx, sprites, x, y);
	else if (x == x_max(width_window(mlx)) && y != 0
		&& y != y_max(height_window(mlx)))
		put_right(mlx, sprites, x, y);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->barrels, x
			* TILE, y * TILE);
}
