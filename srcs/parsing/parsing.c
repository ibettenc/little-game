/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:57:15 by raantoin          #+#    #+#             */
/*   Updated: 2026/08/07 13:59:30 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*get_next_line(int fd);

int	parser(char *full_file, t_map_par *map_par)
{
	char	**file_text;
	char	*buffer;
	int		file_fd;
	int		i;

	i = file_len_nb(full_file);
	file_text = malloc((i + 1) * sizeof(char *));
	i = 0;
	file_fd = open(full_file, O_RDONLY);
	buffer = get_next_line(file_fd);
	while (buffer != NULL)
	{
		file_text[i] = buffer;
		i++;
		buffer = get_next_line(file_fd);
	}
	file_text[i] = NULL;
	if (file_sorter(file_text, map_par, full_file) == 0)
	{
		free_file_text(file_text);
		free_all(map_par);
		return (close (file_fd), 0);
	}
	free_file_text(file_text);
	return (close (file_fd), 1);
}

int	file_len_nb(char *file_path)
{
	char	*buffer;
	int		line_nb;
	int		file_fd;

	line_nb = 0;
	file_fd = open(file_path, O_RDONLY);
	buffer = get_next_line(file_fd);
	while (buffer != NULL)
	{
		line_nb++;
		free(buffer);
		buffer = get_next_line(file_fd);
	}
	close(file_fd);
	return (line_nb);
}

int	skip_spaces(int j, char *line)
{
	while (line[j] == ' ')
		j++;
	return (j);
}

int	file_sorter(char **file, t_map_par *map_par, char *full_file)
{
	int	i;
	int	j;

	i = 0;
	if (check_dup(file, map_par) == 0
		|| map_memory(file, map_par, full_file) == 0)
		return (0);
	while (file[i])
	{
		j = 0;
		j = skip_spaces(j, file[i]);
		if (sorter_colour(file, i, j, map_par) == 0
			|| sorter_walls(file, i, j, map_par) == 0)
			return (0);
		i++;
	}
	if (map_check(map_par) == 0)
	{
		printf("Error, map has invalid characters or number of players\n");
		return (0);
	}
	if (accessible(map_par))
		return (1);
	return (0);
}
