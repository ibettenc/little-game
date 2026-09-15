/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:19:22 by raantoin          #+#    #+#             */
/*   Updated: 2026/08/05 17:55:21 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "srcs/includes/libft/libft.h"
# include "srcs/includes/mlx/mlx.h"
# include "srcs/includes/GNL/get_next_line.h"
# include <math.h>

# define WIN_WIDTH   1800
# define WIN_HEIGHT  1200
# define WALL_OFFSET 0.2

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;// position dans la map (en cases)
	double	y;
	double	dir_x;// direction
	double	dir_y;
	double	plane_x;// FOV
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_map
{
	char	**grid;// grille 2D
	int		width;
	int		height;
}	t_map;

typedef struct s_ray
{
	int		map_x;// case actuelle dans la map
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_end;
	int		draw_start;
	int		tex_id;
	int		tex_x;
	int		tex_y;
	double	ray_dir_x;// direction du rayon
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;// image buffer principale
	t_img		textures[4];// 0=NO, 1=SO, 2=EA, 3=WE
	char		*textures_paths[4];
	t_player	player;
	t_map		map;
	int			floor_color[3];
	int			ceil_color[3];
	int			keys[6];
}	t_game;

typedef struct s_graph
{
	void	*wall_east;
	void	*wall_west;
	void	*wall_south;
	void	*wall_north;
	void	*cha;

}	t_graph;

typedef struct s_map_par
{
	int		init_pos[2];
	char	**map;
	void	*img;
	int		line_len;
	int		line_nb;
	int		size_x;
	int		size_y;
	char	*title;
	void	*exit;
	void	*mlx;
	void	*win;
	char	*floor;
	char	*ceiling;
	int		map_error;
	int		char_found;
	int		char_pos[2];
	char	*texture_paths[4];
	int		last_info_ln;
	t_graph	*graph;
	t_game	game;
}	t_map_par;

/* main.c */
int		check_arg(int argc, char **argv);
void	free_game(t_game *game);
void	init_map(t_map_par *map_par);
void	set_colors(int colors[3], char *str);
int		close_window(t_map_par *map_par);
int		game_loop(t_game *game);

/* PARSING */

/* file_errors.c */
void	check_dup_helper(int *count, int pos[2],
			char **file, t_map_par *map_par);
int		valid_colours(char *colour);
int		check_dup(char **file, t_map_par *map_par);
int		check_text(char *path, char *direction, t_map_par *map_par);

/* floodfill.c*/
char	**copy_map(t_map_par *map_par);
int		accessible(t_map_par *map_par);
void	flood_fill(char **map_copy, int i, int j, t_map_par *map_par);
int		all_flood(t_map_par *map_par, char **map_copy);

/* floodfill2.c */
int		valid_map_char(t_map_par *map_par, char **map_copy);
char	**rectangularize(t_map_par *map_par);

/* map_parsing.c */
void	find_char_start(t_map_par *map_par, char **map_copy);
int		map_memory(char **file, t_map_par *map_par, char *full_file);
int		empty_line(char *file);
int		map_check(t_map_par *map_par);
int		get_line_len(char *line);
void	free_str(char **str);
void	assign_values(t_map_par *map_par, int line_length, int j, char **map);
void	free_file_text(char **file_text);
void	remove_newline(char *line);

/*parsing.c*/
int		parser(char *full_file, t_map_par *map_par);
int		file_len_nb(char *file_path);
int		skip_spaces(int j, char *line);
int		file_sorter(char **file, t_map_par *map_par, char *full_file);
int		sorter_walls(char **file, int i, int j, t_map_par *map_par);
int		sorter_colour(char **file, int i, int j, t_map_par *map_par);
void	free_all(t_map_par *map_par);

/* RENDER */

/* movement.c */
void	handle_movement(t_game *game);

/* player.c */
void	init_player(t_game *game);

/* raycasting.c */
void	perform_dda(t_game *game, t_ray *ray);
void	calcul_column(t_ray *ray);
void	draw_column(t_game *game, t_ray *ray, int x);
void	raycast(t_game *game);

/* raycasting_utils.c */
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_dda(t_game *game, t_ray *ray);

/* render.c */
void	put_pixel(t_img *img, int x, int y, int color);
void	load_textures(t_game *game);
void	get_data_addr(t_game *game);
int		get_tex_id(t_ray *ray);
int		get_tex_x(t_game *game, t_ray *ray);
void	draw_textured_wall(t_game *game, t_ray *ray, int x);

/* UTILS */

/* rgb_to_hex.c */
int		rgb_to_hex(unsigned char r, unsigned char g, unsigned char b);

/* mlx_init.c */
void	init_mlx(t_game *game);

/* hooks.c */
int		key_press(int key, t_map_par *map_par);
int		key_release(int key, t_game *game);

#endif
