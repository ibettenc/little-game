/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:29:09 by raantoin          #+#    #+#             */
/*   Updated: 2026/07/25 18:23:35 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			i;

	temp = ((unsigned char *)s);
	i = 0;
	while (i < n)
	{
		temp[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
