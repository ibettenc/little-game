/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:28:43 by raantoin          #+#    #+#             */
/*   Updated: 2026/05/13 14:38:52 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char	*stash_line(char *stash)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	j = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	newline = malloc(i + 2);
	if (!newline)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		newline[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		newline[i++] = '\n';
	newline[i] = '\0';
	while (stash[i] != '\0')
		stash[j++] = stash[i++];
	stash[j] = '\0';
	return (newline);
}

char	*add_buffer(char *stash, char *buffer)
{
	char	*result;

	result = ft_strjoin(stash, buffer);
	free(stash);
	return (result);
}

char	*stash_creation(char *stash)
{
	if (!stash)
	{
		stash = malloc(BUFFER_SIZE + 1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	return (stash);
}

void	gnl_helper(int *fd, char **stash, int *bytesread, char *buffer)
{
	while (ft_strchr(*stash, '\n') == NULL)
	{
		*bytesread = read(*fd, buffer, BUFFER_SIZE);
		if (*bytesread <= 0)
			break ;
		buffer[*bytesread] = '\0';
		*stash = add_buffer(*stash, buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*result;
	int			bytesread;
	char		buffer[BUFFER_SIZE + 1];

	result = NULL;
	if (BUFFER_SIZE <= 0 || fd <= -1)
		return (NULL);
	stash = stash_creation(stash);
	bytesread = 1;
	gnl_helper(&fd, &stash, &bytesread, buffer);
	if (stash[0] != '\0')
		result = stash_line(stash);
	if ((bytesread == 0) || !result)
	{
		free(stash);
		stash = NULL;
	}
	return (result);
}
