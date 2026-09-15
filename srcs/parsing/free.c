/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 22:03:03 by raantoin          #+#    #+#             */
/*   Updated: 2026/08/06 19:06:27 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_all(t_map_par *map_par)
{
	int	i;

	i = 0;
	free_game(&map_par->game);
	if (map_par->map)
	{
		while (map_par->map[i])
		{
			free(map_par->map[i]);
			i++;
		}
	}
	free(map_par->ceiling);
	free(map_par->floor);
	if (map_par->map)
		free(map_par->map);
	i = 0;
	while (i < 4)
	{
		free(map_par->texture_paths[i]);
		i++;
	}
	free(map_par);
}

void	free_file_text(char **file_text)
{
	int	i;

	i = 0;
	while (file_text[i])
	{
		if (file_text[i])
			free(file_text[i]);
		i++;
	}
	free(file_text);
}
