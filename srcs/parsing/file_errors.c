/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:15:46 by raantoin          #+#    #+#             */
/*   Updated: 2026/08/06 18:05:02 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	valid_colours(char *colour)
{
	int		i;
	int		nb;
	int		nb_count;
	char	**numbers;

	i = 0;
	nb_count = 0;
	numbers = ft_split(colour, ',');
	while (numbers[i])
	{
		nb = ft_atoi(numbers[i]);
		free(numbers[i]);
		if (nb < 0 || nb > 255)
		{
			free(numbers);
			return (printf("Error! invalid colour values\n"), 0);
		}
		nb_count++;
		i++;
	}
	free(numbers);
	if (nb_count == 3)
		return (1);
	printf("Error\n invalid number of colour parameters\n");
	return (0);
}

int	sorter_colour(char **file, int i, int j, t_map_par *map_par)
{
	if (file[i][j] == 'F')
	{
		j++;
		j = skip_spaces(j, file[i]);
		if (valid_colours(&file[i][j]))
			map_par->floor = ft_strdup(&file[i][j]);
		else
			return (0);
	}
	if (file[i][j] == 'C')
	{
		j++;
		j = skip_spaces(j, file[i]);
		if (valid_colours(&file[i][j]))
			map_par->ceiling = ft_strdup(&file[i][j]);
		else
			return (0);
	}
	return (1);
}

int	check_dup(char **file, t_map_par *map_par)
{
	int	pos[2];
	int	count[6];

	pos[0] = 0;
	while (pos[0] < 6)
		count[pos[0]++] = 0;
	pos[0] = 0;
	while (file[pos[0]])
	{
		pos[1] = 0;
		check_dup_helper(count, pos, file, map_par);
		pos[0]++;
	}
	pos[0] = 0;
	while (pos[0] < 6)
	{
		if (count[pos[0]] != 1)
		{
			printf("Error the file has missing or duplicate values!\n");
			return (0);
		}
		pos[0]++;
	}
	return (1);
}

void	check_dup_helper(int *nb, int p[2], char **f, t_map_par *map_par)
{
	int	k;

	k = 0;
	p[1] = skip_spaces(p[1], f[p[0]]);
	if (f[p[0]][p[1]] == 'F')
		nb[0]++;
	if (f[p[0]][p[1]] == 'C')
		nb[1]++;
	if (f[p[0]][p[1]] == 'W' && f[p[0]][p[1] + 1] && f[p[0]][p[1] + 1] == 'E')
		nb[2]++;
	if (f[p[0]][p[1]] == 'E' && f[p[0]][p[1] + 1] && f[p[0]][p[1] + 1] == 'A')
		nb[3]++;
	if (f[p[0]][p[1]] == 'N' && f[p[0]][p[1] + 1] && f[p[0]][p[1] + 1] == 'O')
		nb[4]++;
	if (f[p[0]][p[1]] == 'S' && f[p[0]][p[1] + 1] && f[p[0]][p[1] + 1] == 'O')
		nb[5]++;
	while (k < 6 && nb[k] == 1)
	{
		if (k == 5 && map_par->last_info_ln == 0)
			map_par->last_info_ln = p[0];
		k++;
	}
}

int	check_text(char *path, char *direction, t_map_par *map_par)
{
	char	*new_path;
	int		fd;
	int		len;

	new_path = ft_strdup(path + skip_spaces(0, path));
	if (!new_path)
		return (0);
	len = ft_strlen(new_path);
	if (len > 0 && new_path[len - 1] == '\n')
		new_path[len - 1] = '\0';
	fd = open(new_path, O_RDONLY);
	if (fd == -1)
		return (free(new_path), 0);
	close(fd);
	if (ft_strncmp(direction, "NO", 2) == 0)
		map_par->texture_paths[0] = new_path;
	if (ft_strncmp(direction, "SO", 2) == 0)
		map_par->texture_paths[1] = new_path;
	if (ft_strncmp(direction, "EA", 2) == 0)
		map_par->texture_paths[2] = new_path;
	if (ft_strncmp(direction, "WE", 2) == 0)
		map_par->texture_paths[3] = new_path;
	return (1);
}
