/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:53:00 by raantoin          #+#    #+#             */
/*   Updated: 2026/08/04 18:46:15 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	**copy_map(t_map_par *map_par)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	copy = malloc(sizeof(char *) * (map_par->line_nb + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map_par->map[i])
	{
		copy[i] = malloc(sizeof(char) * (map_par->line_len + 1));
		if (!copy[i])
			return (NULL);
		j = 0;
		while (map_par->map[i][j])
		{
			copy[i][j] = map_par->map[i][j];
			j++;
		}
		copy[i][map_par->line_len] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	accessible(t_map_par *map_par)
{
	char	**map_copy;

	map_copy = rectangularize(map_par);
	if (!map_copy)
		return (printf("Error, map can't be rectangularized!\n"), 0);
	map_par->char_found = 0;
	find_char_start(map_par, map_copy);
	if (all_flood(map_par, map_copy) == 0)
	{
		free_str(map_copy);
		return (printf("Error, map isn't properly walled \n"), 0);
	}
	free_str(map_copy);
	if (map_par->char_found)
		return (1);
	write(1, "Error, elements are not reachable\n", 35);
	return (0);
}

void	flood_fill(char **map_copy, int i, int j, t_map_par *map_par)
{
	if (i < 0 || j < 0 || i >= map_par->line_nb || j >= map_par->line_len)
	{
		map_par->map_error = 1;
		return ;
	}
	if (map_copy[i][j] == ' ')
	{
		map_par->map_error = 1;
		return ;
	}
	if (map_copy[i][j] == '1' || map_copy[i][j] == '2')
		return ;
	map_copy[i][j] = '2';
	flood_fill(map_copy, i + 1, j, map_par);
	flood_fill(map_copy, i - 1, j, map_par);
	flood_fill(map_copy, i, j + 1, map_par);
	flood_fill(map_copy, i, j - 1, map_par);
}

int	all_flood(t_map_par *map_par, char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	map_par->map_error = 0;
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len)
		{
			if (map_copy[i][j] == '0')
				flood_fill(map_copy, i, j, map_par);
			j++;
		}
		i++;
	}
	flood_fill(map_copy, map_par->char_pos[0], map_par->char_pos[1], map_par);
	if (valid_map_char(map_par, map_copy) == 0 || map_par->map_error == 1)
		return (0);
	return (1);
}

int	valid_map_char(t_map_par *map_par, char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len && map_copy[i][j])
		{
			if (map_copy[i][j] != '2' && map_copy[i][j] != '1'
				&& map_copy[i][j] != ' ')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
