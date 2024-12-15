/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:13 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/15 19:32:22 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/**
 * @brief Allocates memory for a new linked list node and its content buffer.
 * @return a pointer to the newly created
 * 	node, or NULL if memory allocation fails
 */
t_list	*malloc_new_t_list(void)
{
	t_list			*new_node;
	unsigned int	i;

	i = 0;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = (char *)malloc(BUFFER_SIZE + 1);
	if (!new_node->content)
	{
		free(new_node);
		return ((void *)0);
	}
	while (i < BUFFER_SIZE + 1)
	{
		new_node->content[i] = 0;
		i++;
	}
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Searches for a newline character in the content of the given node.
 * @param new_node a pointer to the node to be searched
 * @return the index of the newline character if found, or -1 if not found
 */
int	find_new_line(t_list *new_node, int *no_new_line)
{
	int	i;

	i = 0;
	if (!new_node || !new_node->content || !no_new_line)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (new_node->content[i] == '\n' || new_node->content[i] == '\0')
		{
			if (new_node->content[i] == '\n')
				return (i);
			if (new_node->content[i] == '\0')
			{
				*no_new_line = 1;
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

/**
 * @param s a pointer to the first char of s
 * @brief Duplicates the array of char to a new char of arrays.
 */
char	*ft_strdup(char *s)
{
	int		index;
	char	*string_dup;
	int		s_size;

	index = 0;
	s_size = 0;
	while (s[index])
	{
		index++;
		s_size++;
	}
	string_dup = (char *)malloc((s_size + 1) * sizeof(char));
	if (string_dup == (void *)0)
		return ((void *)0);
	index = 0;
	while (s[index])
	{
		string_dup[index] = s[index];
		index++;
	}
	string_dup[s_size] = '\0';
	return (string_dup);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	dest_size;
	size_t	src_size;

	i = 0;
	dest_size = 0;
	src_size = 0;
	if (!dst || !src || size <= 0)
		return (0);
	while (src[src_size] && src[src_size] != '\n')
		src_size++;
	while (dst[dest_size] && dest_size < size)
		dest_size++;
	if (size == 0)
		return (src_size);
	while (dest_size + i < size && src[i])
	{
		dst[dest_size + i] = src[i];
		i++;
	}
	dst[dest_size + i] = '\0';
	if (size <= dest_size)
		return (src_size + size);
	return (dest_size + src_size);
}

/**
 * @brief Frees the memory allocated for the linked list.
 * @param list a pointer to the head of the linked list
 */
void	free_memory_assign_new_content(t_list **node_to_be_freed, t_list *tmp,
		int pos_n)
{
	t_list	*next_tmp;
	char	*new_content;

	if (!node_to_be_freed || !*node_to_be_freed || !tmp || pos_n < 0)
		return ;
	while ((*node_to_be_freed) != tmp)
	{
		next_tmp = (*node_to_be_freed)->next;
		free((*node_to_be_freed)->content);
		free(*node_to_be_freed);
		(*node_to_be_freed) = next_tmp;
	}
	new_content = ft_strdup(tmp->content + pos_n + 1);
	if (new_content)
	{
		free(tmp->content);
		tmp->content = new_content;
	}
}
