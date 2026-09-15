/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:57:45 by raantoin          #+#    #+#             */
/*   Updated: 2026/06/29 19:29:06 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = (char) c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == ch)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*concat;
	size_t	total_len;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	concat = malloc((total_len + 1) * sizeof(char));
	if (!concat)
		return (NULL);
	j = 0;
	ft_strcpy(&concat[j], &s1[0]);
	j += ft_strlen(s1);
	ft_strcpy(&concat[j], &s2[0]);
	j += ft_strlen(s2);
	concat[j] = '\0';
	return (concat);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	size_t		len_src;
	char		*new_src;
	int			i;	

	i = 0;
	len_src = ft_strlen(src);
	new_src = (char *)malloc((len_src + 1) * sizeof(char));
	if (!new_src)
	{
		return (NULL);
	}
	while (src[i] != '\0')
	{
		new_src[i] = src[i];
		i++;
	}
	new_src[i] = '\0';
	return (new_src);
}
