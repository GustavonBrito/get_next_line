/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:13 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/11/24 16:49:03 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*malloc_new_t_list(void)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = (char *)malloc(sizeof(BUFFER_SIZE + 1));
	if (!new_node->content)
	{
		free(new_node->content);
		return ((void *)0);
	}
	new_node->next = NULL;
	return (new_node);
}

int	find_new_line(t_list *new_node)
{
	int	i;

	i = 0;
	if (!new_node || !new_node->content)
		return -1;
	while (i < BUFFER_SIZE)
	{
		if (new_node->content[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	dest_len;

	i = 0;
	dest_len = 0;
	while (dest[dest_len])
	{
		dest_len++;
	}
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}