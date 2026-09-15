/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:16:33 by raantoin          #+#    #+#             */
/*   Updated: 2026/07/25 19:27:14 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

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

	len_src = ft_strlen(src);
	new_src = (char *)malloc((len_src + 1) * sizeof(char));
	if (!new_src)
	{
		return (NULL);
	}
	ft_strcpy(new_src, src);
	return (new_src);
}
