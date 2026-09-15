/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 20:55:32 by raantoin          #+#    #+#             */
/*   Updated: 2026/08/05 17:31:46 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	fill_map(char **file, char **map, int i, t_map_par *map_par)
{
	int		j;
	size_t	line_length;

	j = 0;
	line_length = 0;
	while (file[i + j] && !empty_line(file[i + j]))
	{
		remove_newline(file[i + j]);
		map[j] = ft_strdup(file[i + j]);
		if (ft_strlen(file[i + j]) > line_length)
			line_length = ft_strlen(file[i + j]);
		j++;
	}
	map[j] = NULL;
	assign_values(map_par, line_length, j, map);
}

int	map_memory(char **file, t_map_par *map_par, char *full_file)
{
	char	**map;
	int		i;

	i = map_par->last_info_ln + 1;
	while (file[i] && empty_line(file[i]))
		i++;
	if (!file[i])
		return (printf("Error! No map detected!\n"), 0);
	map = malloc((file_len_nb(full_file) - i + 1) * sizeof(char *));
	if (!map)
		return (printf("Error, map memory allocation fail\n"), 0);
	fill_map(file, map, i, map_par);
	return (1);
}

void	assign_values(t_map_par *map_par, int line_length, int j, char **map)
{
	map_par->line_len = line_length;
	map_par->line_nb = j;
	map_par->map = map;
}

void	remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	empty_line(char *file_line)
{
	int	i;

	i = 0;
	while (file_line[i])
	{
		if (file_line[i] == ' ' || file_line[i] == '\t' || file_line[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}
