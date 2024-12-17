/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:13 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/17 14:53:17 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	s_length;

	s_length = 0;
	while (*s)
	{
		s_length++;
		s++;
	}
	return (s_length);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (c > 255)
		c = c % 256;
	while (s[i])
	{
		if (s[i] == c)
			return (s = &s[i]);
		i++;
	}
	if (c == 0)
		return (s = &s[i]);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	k;
	unsigned int	i;
	unsigned int	j;
	char			*pointer_malloc;

	if (s1 && s2)
	{
		i = ft_strlen(s1);
		j = ft_strlen(s2);
		k = -1;
		pointer_malloc = (char *)malloc(sizeof(char) * (i + j + 1));
		if (pointer_malloc == ((void *)0))
			return ((void *)0);
		while (s1[++k])
			pointer_malloc[k] = s1[k];
		k = -1;
		while (s2[++k])
		{
			pointer_malloc[i] = s2[k];
			i++;
		}
		pointer_malloc[i] = '\0';
		return (pointer_malloc);
	}
	return ((void *)0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	src_size;

	src_size = 0;
	i = 0;
	while (src[i])
	{
		i++;
		src_size++;
	}
	if (size == 0)
		return (src_size);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_size);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_unsigned;
	unsigned int	c_unsigned;
	unsigned int	i;

	s_unsigned = s;
	c_unsigned = c;
	i = 0;
	if (n == 0)
		return (s_unsigned);
	while (i < n)
	{
		s_unsigned[i] = c_unsigned;
		i++;
	}
	return (s_unsigned);
}
