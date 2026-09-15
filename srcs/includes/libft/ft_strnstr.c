/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:31:19 by raantoin          #+#    #+#             */
/*   Updated: 2026/07/25 19:26:53 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *l, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (l[i] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] == l[j] && (i + j) < len && l[j] && big[i + j])
			j++;
		if (j == ft_strlen(l))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
