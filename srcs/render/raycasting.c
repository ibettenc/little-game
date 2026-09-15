/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:17:36 by ibettenc          #+#    #+#             */
/*   Updated: 2026/08/05 17:16:03 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (game->map.grid[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

void	calcul_column(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = WIN_HEIGHT / ray->perp_wall_dist;
	ray->draw_start = WIN_HEIGHT / 2 - ray->line_height / 2;
	ray->draw_end = WIN_HEIGHT / 2 + ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int				y;
	unsigned int	color_hex;

	calcul_column(ray);
	ray->tex_id = get_tex_id(ray);
	ray->tex_x = get_tex_x(game, ray);
	color_hex = rgb_to_hex(game->ceil_color[0],
			game->ceil_color[1], game->ceil_color[2]);
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->screen, x, y, color_hex);
		y++;
	}
	draw_textured_wall(game, ray, x);
	y = ray->draw_end + 1;
	color_hex = rgb_to_hex(game->floor_color[0],
			game->floor_color[1], game->floor_color[2]);
	while (y < WIN_HEIGHT)
	{
		put_pixel(&game->screen, x, y, color_hex);
		y++;
	}
}

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		init_ray(game, &ray, x);
		init_dda(game, &ray);
		perform_dda(game, &ray);
		calcul_column(&ray);
		draw_column(game, &ray, x);
		x++;
	}
}
