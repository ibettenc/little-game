/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:11:22 by raantoin          #+#    #+#             */
/*   Updated: 2026/07/25 19:26:58 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	ch;

	i = ft_strlen(s);
	ch = (char) c;
	if (ch == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		if (s[i - 1] == ch)
			return ((char *)&s[i - 1]);
		i--;
	}
	return (NULL);
}
