/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:17:34 by ibettenc          #+#    #+#             */
/*   Updated: 2026/08/06 19:08:07 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	load_textures(t_game *game)
{
	game->textures[0].img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->textures_paths[0], &game->textures[0].width,
			&game->textures[0].height);
	game->textures[1].img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->textures_paths[1], &game->textures[1].width,
			&game->textures[1].height);
	game->textures[2].img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->textures_paths[2], &game->textures[2].width,
			&game->textures[2].height);
	game->textures[3].img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->textures_paths[3], &game->textures[3].width,
			&game->textures[3].height);
}

void	get_data_addr(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].addr = mlx_get_data_addr(
				game->textures[i].img_ptr,
				&game->textures[i].bpp,
				&game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
}

int	get_tex_id(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if (ray->step_y > 0)
			return (3);
		else
			return (2);
	}
}

int	get_tex_x(t_game *game, t_ray *ray)
{
	double	ray_impact;

	if (ray->side == 0)
		ray_impact = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray_impact = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray_impact = ray_impact - floor(ray_impact);
	return ((int)(ray_impact * game->textures[ray->tex_id].width));
}

void	draw_textured_wall(t_game *game, t_ray *ray, int x)
{
	double	step_tex;
	double	tex_pos;
	int		color;
	char	*tex_addr;
	int		y;

	step_tex = (double)game->textures[ray->tex_id].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT
			/ 2 + ray->line_height / 2) * step_tex;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int)tex_pos & (game->textures[ray->tex_id].height - 1);
		tex_pos += step_tex;
		tex_addr = game->textures[ray->tex_id].addr
			+ (ray->tex_y * game->textures[ray->tex_id].line_len
				+ ray->tex_x * (game->textures[ray->tex_id].bpp / 8));
		color = *(unsigned int *)tex_addr;
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(&game->screen, x, y, color);
		y++;
	}
}
