/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 17:22:46 by ibettenc          #+#    #+#             */
/*   Updated: 2026/08/06 19:05:46 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_arg(int argc, char **argv)
{
	int	n;
	int	fd;

	if (argc != 2)
	{
		printf("Error! Incorrect number of arguments!\n");
		return (0);
	}
	n = ft_strlen(argv[1]);
	if ((n <= 4) || ft_strncmp(&argv[1][n - 4], ".cub", 4) != 0)
	{
		printf("Error, the file must be of format .cub\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error, invalid file descriptor!\n");
		return (0);
	}
	else
		close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map_par	*map_par;

	map_par = malloc(sizeof(t_map_par));
	ft_memset(map_par, 0, sizeof(t_map_par));
	ft_memset(&map_par->game, 0, sizeof(t_game));
	if (check_arg(argc, argv) == 0)
		return (free(map_par), 0);
	if (!parser(argv[1], map_par))
		return (0);
	init_map(map_par);
	init_player(&map_par->game);
	init_mlx(&map_par->game);
	mlx_hook(map_par->game.win, 2, 1L << 0, key_press, map_par);
	mlx_hook(map_par->game.win, 17, 0, close_window, map_par);
	mlx_loop_hook(map_par->game.mlx, game_loop, &map_par->game);
	mlx_loop(map_par->game.mlx);
	return (0);
}

void	init_map(t_map_par *map_par)
{
	map_par->game.map.grid = map_par->map;
	map_par->game.map.width = map_par->line_len;
	map_par->game.map.height = map_par->line_nb;
	map_par->game.textures_paths[0] = map_par->texture_paths[0];
	map_par->game.textures_paths[1] = map_par->texture_paths[1];
	map_par->game.textures_paths[2] = map_par->texture_paths[2];
	map_par->game.textures_paths[3] = map_par->texture_paths[3];
	set_colors(map_par->game.ceil_color, map_par->ceiling);
	set_colors(map_par->game.floor_color, map_par->floor);
}

void	set_colors(int colors[3], char *str)
{
	char	**numbers;
	int		i;

	numbers = ft_split(str, ',');
	i = 0;
	while (numbers[i])
	{
		colors[i] = ft_atoi(numbers[i]);
		free(numbers[i]);
		i++;
	}
	free(numbers);
}

int	game_loop(t_game *game)
{
	handle_movement(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->screen.img_ptr, 0, 0);
	return (0);
}
