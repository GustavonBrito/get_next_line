/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:11 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/14 21:16:43 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Appends the content of the linked list
 *		nodes to a buffer until a newline character is found.
 * @param current a pointer to the current node of the linked list
 * @param buffer_len the total length of the buffer to be allocated
 * @return a pointer to the newly allocated
 * 		buffer containing the concatenated content
 */
char	*append_buffer_until_n(t_list *current, int buffer_len,
		int *ptr_no_new_line)
{
	unsigned int	i;
	unsigned int	tmp_i;
	char			*buffer_to_return;

	i = BUFFER_SIZE;
	tmp_i = i;
	buffer_to_return = (char *)malloc(sizeof(char) * (buffer_len + 2));
	if (!buffer_to_return)
		return ((void *)0);
	if (buffer_len < 0 || current == NULL)
		return (NULL);
	buffer_to_return[0] = '\0';
	while (ft_strlcat(buffer_to_return, current->content, buffer_len) == i)
	{
		i += tmp_i;
		current = current->next;
	}
	if (*ptr_no_new_line == 1)
		buffer_to_return[buffer_len] = '\0';
	else
	{
		buffer_to_return[buffer_len] = '\n';
		buffer_to_return[buffer_len + 1] = '\0';
	}
	return (buffer_to_return);
}

/**
 * @param tmp a pointer to pointer to alter
 * @param fd file descriptor of a file or STDIN
 * @param buffer_len the buffer length returned until n
 * @brief Finds the new line and returns the buffer_len until n
 */
int	find_n(t_list **tmp, int fd, int buffer_len, int *ptr_no_new_line)
{
	ssize_t	size_read;

	size_read = 0;
	while (find_new_line(*tmp, ptr_no_new_line) == -1)
	{
		buffer_len += BUFFER_SIZE;
		(*tmp)->next = malloc_new_t_list();
		*tmp = (*tmp)->next;
		size_read = read(fd, (*tmp)->content, BUFFER_SIZE);
		if (size_read < 0)
			return (-1);
		(*tmp)->content[size_read] = '\0';
	}
	buffer_len += find_new_line(*tmp, ptr_no_new_line);
	return (buffer_len);
}

/**
* @param list a pointer to pointer to alter
	directly the new head of the linked list
 * @param fd file descriptor of a file or STDIN
 * @brief Finds the new line and calls a function to return the buffer
 */
char	*find_n_return_buffer(t_list **list, int fd, int *ptr_no_new_line)
{
	int		buffer_len;
	int		pos_n;
	char	*buffer;
	t_list	*tmp;

	tmp = *list;
	buffer_len = 0;
	pos_n = 0;
	buffer_len = find_n(&tmp, fd, buffer_len, ptr_no_new_line);
	if (buffer_len == -1)
		return (NULL);
	buffer = append_buffer_until_n(*list, buffer_len, ptr_no_new_line);
	pos_n = find_new_line(tmp, ptr_no_new_line);
	free_memory_assign_new_content(list, tmp, pos_n);
	return (buffer);
}

/**
 * @brief Reads a line from a file descriptor and stores it in a linked list.
 * @param fd the file descriptor to read from
 * @param list a pointer to pointer to alter
 * 	directly the new head of the linked list
 * @return a buffer of char* type
 */
char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*buffer;
	int				no_new_line;
	int				*ptr_no_new_line;

	buffer = NULL;
	no_new_line = 0;
	ptr_no_new_line = &no_new_line;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!head)
	{
		head = malloc_new_t_list();
		if (!head || read(fd, head->content, BUFFER_SIZE) <= 0
			|| head->content[0] == '\0')
		{
			free(head->content);
			free(head);
			head = NULL;
			return (NULL);
		}
	}
	buffer = find_n_return_buffer(&head, fd, ptr_no_new_line);
	return (buffer);
}

int	main(void)
{
	int	fd;
	char *buffer;
	//int i;

	//i = 0;
	fd = open("arquivo.txt", O_RDONLY);
	buffer = get_next_line(fd);
	printf("%s",buffer);
	free(buffer);
	// while (i < 6)
	// {
	// 	buffer = get_next_line(fd);
	// 	printf("%s", buffer);
	// 	free(buffer);
	// 	i++;
	// }
	close(fd);
	return (0);
}
