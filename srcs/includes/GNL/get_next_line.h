/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:00:08 by raantoin          #+#    #+#             */
/*   Updated: 2026/06/29 19:28:55 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# include <stddef.h>
# include <unistd.h>

char				*ft_strcpy(char *dest, const char *src);
char				*get_next_line(int fd);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *src);
char				*ft_strncat(char *dest, const char *src, unsigned int nb);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strcopy(char *dest, char const *src);
char				*ft_strjoin(char const *s1, char const *s2);

#endif
