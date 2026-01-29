/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:31:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 13:10:45 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	put_floor(t_data *mlx, t_sprites *sprites, int x, int y)
{
	if (!sprites->floorblue || !sprites->floorwhite)
		return ;
	if ((x + y) % 2 == 0)
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->floorblue, x
			* TILE, y * TILE);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->floorwhite, x
			* TILE, y * TILE);
}

void	put_collectible(t_data *mlx, t_sprites *sprites, int x, int y)
{
	if (!sprites->cheese)
		return ;
	mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->cheese, x * TILE, y
		* TILE);
}

void	put_exit(t_data *mlx, t_sprites *sprites, int x, int y)
{
	if (!sprites->exit)
		return ;
	mlx_put_image_to_window(mlx->mlx, mlx->window, sprites->exit, x * TILE, y
		* TILE);
}
