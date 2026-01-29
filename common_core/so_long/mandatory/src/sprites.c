/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:18:28 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 23:36:41 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	*load_sprite(void *mlx, char *path)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
	{
		free(img);
		ft_printf("Erreur chargement sprite : %s\n", path);
	}
	return (img);
}

void	load_player(t_data *m, t_sprites *sprites)
{
	sprites->playerbottomleft = load_sprite(m->mlx,
			"assets/jerry_bottom/bottomleft3.xpm");
	sprites->playerbottommid = load_sprite(m->mlx,
			"assets/jerry_bottom/bottommid.xpm");
	sprites->playerbottomright = load_sprite(m->mlx,
			"assets/jerry_bottom/bottomright3.xpm");
	sprites->playerleftleft = load_sprite(m->mlx,
			"assets/jerry_left/leftleft3.xpm");
	sprites->playerleftmid = load_sprite(m->mlx,
			"assets/jerry_left/leftmid.xpm");
	sprites->playerleftright = load_sprite(m->mlx,
			"assets/jerry_left/leftright3.xpm");
	sprites->playerrightleft = load_sprite(m->mlx,
			"assets/jerry_right/rightleft3.xpm");
	sprites->playerrightmid = load_sprite(m->mlx,
			"assets/jerry_right/rightmid.xpm");
	sprites->playerrightright = load_sprite(m->mlx,
			"assets/jerry_right/rightright3.xpm");
	sprites->playertopright = load_sprite(m->mlx,
			"assets/jerry_top/topright3.xpm");
	sprites->playertopmid = load_sprite(m->mlx, "assets/jerry_top/topmid.xpm");
	sprites->playertopleft = load_sprite(m->mlx,
			"assets/jerry_top/topleft3.xpm");
}

void	load_map(t_data *m, t_sprites *sprites)
{
	sprites->wallbluebottom = load_sprite(m->mlx,
			"assets/wall/wallbluebottom.xpm");
	sprites->wallblueleft = load_sprite(m->mlx, "assets/wall/wallblueleft.xpm");
	sprites->wallblueright = load_sprite(m->mlx,
			"assets/wall/wallblueright.xpm");
	sprites->wallbluetop = load_sprite(m->mlx, "assets/wall/wallbluetop.xpm");
	sprites->wallwhitebottom = load_sprite(m->mlx,
			"assets/wall/wallwhitebottom.xpm");
	sprites->wallwhiteleft = load_sprite(m->mlx,
			"assets/wall/wallwhiteleft.xpm");
	sprites->wallwhiteright = load_sprite(m->mlx,
			"assets/wall/wallwhiteright.xpm");
	sprites->wallwhitetop = load_sprite(m->mlx, "assets/wall/wallwhitetop.xpm");
	sprites->floorblue = load_sprite(m->mlx, "assets/floor/floorblue.xpm");
	sprites->floorwhite = load_sprite(m->mlx, "assets/floor/floorwhite.xpm");
	sprites->barrels = load_sprite(m->mlx, "assets/utils/barrel.xpm");
}

void	load_utils(t_data *m, t_sprites *sprites)
{
	sprites->cheese = load_sprite(m->mlx, "assets/cheese/cheese.xpm");
	sprites->exit = load_sprite(m->mlx, "assets/utils/doorleft.xpm");
}

void	load_all(t_data *m)
{
	load_player(m, &m->sprites);
	load_map(m, &m->sprites);
	load_utils(m, &m->sprites);
}
