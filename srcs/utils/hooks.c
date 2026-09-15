/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:16:27 by ibettenc          #+#    #+#             */
/*   Updated: 2026/08/05 17:17:03 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->screen.img_ptr)
		mlx_destroy_image(game->mlx, game->screen.img_ptr);
	while (i < 4)
	{
		if (game->textures[i].img_ptr)
			mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
		i++;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
}

int	close_window(t_map_par *map_par)
{
	free_all(map_par);
	exit(0);
	return (0);
}

int	key_press(int key, t_map_par *map_par)
{
	if (key == 65307)
		close_window(map_par);
	if (key == 119)
		map_par->game.keys[0] = 1;
	if (key == 97)
		map_par->game.keys[1] = 1;
	if (key == 115)
		map_par->game.keys[2] = 1;
	if (key == 100)
		map_par->game.keys[3] = 1;
	if (key == 65361)
		map_par->game.keys[4] = 1;
	if (key == 65363)
		map_par->game.keys[5] = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 119)
		game->keys[0] = 0;
	if (key == 97)
		game->keys[1] = 0;
	if (key == 115)
		game->keys[2] = 0;
	if (key == 100)
		game->keys[3] = 0;
	if (key == 65361)
		game->keys[4] = 0;
	if (key == 65363)
		game->keys[5] = 0;
	return (0);
}
