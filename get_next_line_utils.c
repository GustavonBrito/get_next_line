/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:13 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/19 20:12:43 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s) + 1;
	dest = (char *)malloc(len);
	if (!dest)
		return (NULL);
	while (*s != '\0')
		dest[i++] = *s++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	size_s;
	size_t	i;

	i = 0;
	size_s = ft_strlen(s);
	if (start > size_s)
		return (ft_strdup(""));
	if (len > size_s - start)
		len = size_s - start;
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	while (i < len)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s3;
	size_t	size;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(size + 1);
	if (!s3)
		return (NULL);
	while (*s1 != '\0')
		s3[i++] = *s1++;
	while (*s2 != '\0')
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}