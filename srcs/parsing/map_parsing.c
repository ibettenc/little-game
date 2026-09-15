/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:59:15 by raantoin          #+#    #+#             */
/*   Updated: 2026/08/05 17:25:18 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	find_char_start(t_map_par *map_par, char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len && map_copy[i][j])
		{
			if (map_copy[i][j] == 'W' || map_copy[i][j] == 'E'
			|| map_copy[i][j] == 'S' || map_copy[i][j] == 'N')
			{
				map_par->char_pos[0] = i;
				map_par->char_pos[1] = j;
				map_par->char_found = 1;
				break ;
			}
			j++;
		}
		i++;
	}
}

char	**rectangularize(t_map_par *map_par)
{
	int		i;
	int		j;
	int		len;
	char	**map_copy;

	i = 0;
	map_copy = copy_map(map_par);
	while (i < map_par->line_nb)
	{
		len = ft_strlen(map_par->map[i]);
		j = len;
		while (j < map_par->line_len)
		{
			map_copy[i][j] = ' ';
			j++;
		}
		if (len > map_par->line_len)
			return (printf("i=%d j=%d len%d\n", i, j, map_par->line_len), NULL);
		map_copy[i][j] = '\0';
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int	sorter_walls(char **file, int i, int j, t_map_par *map_par)
{
	int	ret;

	ret = 1;
	if (file[i][j] == 'W' && file[i][j + 1] == 'E')
		ret *= (check_text(&file[i][j + 2], "WE", map_par));
	if (file[i][j] == 'E' && file[i][j + 1] == 'A')
		ret *= (check_text(&file[i][j + 2], "EA", map_par));
	if (file[i][j] == 'N' && file[i][j + 1] == 'O')
		ret *= (check_text(&file[i][j + 2], "NO", map_par));
	if (file[i][j] == 'S' && file[i][j + 1] == 'O')
		ret *= (check_text(&file[i][j + 2], "SO", map_par));
	if (ret == 0)
	{
		printf("Error ! the file doesn't exist or you don't have access\n");
		return (0);
	}
	return (1);
}

int	map_check(t_map_par *map_par)
{
	int	i;
	int	j;
	int	char_count;

	char_count = 0;
	i = 0;
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len && map_par->map[i][j])
		{
			if (map_par->map[i][j] == 'W' || map_par->map[i][j] == 'E'
			|| map_par->map[i][j] == 'N' || map_par->map[i][j] == 'S')
				char_count++;
			else if (map_par->map[i][j] != ' ' && map_par->map[i][j] != '1'
			&& map_par->map[i][j] != '0' && map_par->map[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	if (char_count != 1)
		return (0);
	return (1);
}
