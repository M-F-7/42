/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:02:34 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/03 23:36:46 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>

# define TILE 32

typedef struct s_maplist
{
	char				*line;
	struct s_maplist	*next;
}						t_maplist;

typedef struct s_sprites
{
	void				*barrels;
	void				*wallbluebottom;
	void				*wallblueleft;
	void				*wallblueright;
	void				*wallbluetop;
	void				*wallwhitebottom;
	void				*wallwhiteleft;
	void				*wallwhiteright;
	void				*wallwhitetop;
	void				*floorblue;
	void				*floorwhite;
	void				*playerbottomleft;
	void				*playerbottommid;
	void				*playerbottomright;
	void				*playerleftleft;
	void				*playerleftmid;
	void				*playerleftright;
	void				*playerrightleft;
	void				*playerrightmid;
	void				*playerrightright;
	void				*playertopright;
	void				*playertopmid;
	void				*playertopleft;
	void				*cheese;
	void				*fakecheese;
	void				*exit;
	void				*enemy1;
	void				*enemy2;
	void				*enemy3;
	void				*jerrydeath;
	void				*trapopen;
	void				*trapclose;
}						t_sprites;

typedef struct s_game
{
	int					player_anim_frame;
	int					player_dir;
	int					enemy_anim_frame;
	int					player_x;
	int					player_y;
	int					player_pos;
	int					collected;
	int					total_collectibles;
	int					steps;
	int					x_max;
	int					y_max;
	int					width_window;
	int					height_window;
}						t_game;

typedef struct s_data
{
	void				*img;
	char				*addr;
	char				**map;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	void				*mlx;
	void				*window;
	t_sprites			sprites;
	t_game				game;
}						t_data;

// UTILS
int						close_window(t_data *vars);
int						key_info(int keycode, t_data *m);
void					free_all(t_data *m);
void					display_steps(t_data *m);

// MAP INFO

int						width_window(t_data *m);
int						height_window(t_data *m);
int						x_max(int x);
int						y_max(int y);

// CREATE MAP
char					**create_map(int fd);
char					**maplist_to_tab(t_maplist *lst, int size);

// MAP
void					map_fill(char **map);
int						nb_lines(int file);
int						check_char(char **tab);
void					map_draw(char **map, t_data *m, t_sprites *sprites);

// SPRITES
void					*load_sprite(void *mlx, char *path);
void					load_player(t_data *m, t_sprites *sprites);
void					load_map(t_data *m, t_sprites *sprites);
void					load_utils(t_data *m, t_sprites *sprites);
void					load_all(t_data *m);

// PLAYER
void					player_forward(t_data *m);
void					player_back(t_data *m);
void					player_left(t_data *m);
void					player_right(t_data *m);
void					find_player_pos(t_data *m);

// PUT PLAYER
void					put_player(t_data *m, t_game *game, int x, int y);

// PUT UTILS
void					put_floor(t_data *mlx, t_sprites *sprites, int x,
							int y);
void					put_collectible(t_data *mlx, t_sprites *sprites, int x,
							int y);
void					put_exit(t_data *mlx, t_sprites *sprites, int x, int y);

// PUT WALL
void					put_wall(t_data *mlx, t_sprites *sprites, int x, int y);

// ERRORS
int						check_errors(t_data *m);
int						check_file(int ac, char **av);
int						check_map(t_data *m);
int						check_content(t_data *m);
int						check_double(t_data *m);

// ERRORS 2
int						check_wall(t_data *m);
int						check_valid_path(t_data *m);

// collect
int						collect(t_data *m);
int						count_collect(t_data *m);

// DESTROY
void					destroy_all(t_data *m, t_sprites *sprites);
void					destroy_player(t_data *m, t_sprites *sprites);
void					destroy_other(t_data *m, t_sprites *sprites);

#endif