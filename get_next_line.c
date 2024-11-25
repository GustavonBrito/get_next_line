/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:11 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/11/25 20:48:55 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

char	*append_buffer_until_n(t_list *current, int total_buffer_len)
{
	int		i;
	int		j;
	char	*buffer_to_return;

	j = 0;
	i = 0;
	buffer_to_return = (char *)malloc(sizeof(char) * total_buffer_len);
	if (!buffer_to_return)
		return ((void *)0);
	while (current)
	{
		i = 0;
		while (current->content[i] != '\n' && current->content[i])
		{
			buffer_to_return[j + i] = current->content[i];
			i++;
		}
		if (current->content[i] == '\n')
			break ;
		j += i;
		current = current->next;
	}
	buffer_to_return[j + i] = '\0';
	return (buffer_to_return);
}

char	*get_n_and_return_buffer(t_list **list, int fd)
{
	int		total_buffer_len;
	int		pos_index;
	char	*buffer;
	t_list	*tmp;
	t_list	*current;

	total_buffer_len = 0;
	tmp = *list;
	while ((pos_index = find_new_line(tmp)) == -1)
	{
		total_buffer_len += BUFFER_SIZE;
		tmp->next = malloc_new_t_list();
		tmp = tmp->next;
		read(fd, tmp->content, BUFFER_SIZE);
	}
	total_buffer_len += pos_index + 1;
	current = *list;
	buffer = (char *)malloc(sizeof(char) * total_buffer_len);
	buffer = append_buffer_until_n(current, total_buffer_len);
	(*list)->content[0] = tmp->content[pos_index + 1];
	return (buffer);
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!head)
	{
		head = malloc_new_t_list();
		if (!head || read(fd, head->content, BUFFER_SIZE) <= 0)
			return (NULL);
	}
	buffer = get_n_and_return_buffer(&head, fd);
	return (buffer);
}

// int	main(void)
// {
// 	int fd;
// 	char *buffer;

// 	fd = 0;
// 	fd = open("arquivo.txt", O_RDONLY);
// 	buffer = get_next_line(fd);

// 	printf("%s\n", buffer);
// 	return (0);
// }