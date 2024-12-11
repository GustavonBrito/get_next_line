/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:11 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/11 01:38:56 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Appends the content of the linked list
 *		nodes to a buffer until a newline character is found.
 * @param current a pointer to the current node of the linked list
 * @param total_buffer_len the total length of the buffer to be allocated
 * @return a pointer to the newly allocated
 * 		buffer containing the concatenated content
 */
char	*append_buffer_until_n(t_list *current, int total_buffer_len)
{
	unsigned int	i;
	unsigned int	tmp_i;
	char			*buffer_to_return;

	i = BUFFER_SIZE;
	tmp_i = i;
	buffer_to_return = (char *)malloc(sizeof(char) * (total_buffer_len + 2));
	if (!buffer_to_return)
		return ((void *)0);
	if (total_buffer_len < 0 || current == NULL)
		return (NULL);
	buffer_to_return[0] = '\0';
	while (ft_strlcat(buffer_to_return, current->content,
			total_buffer_len) == i)
	{
		i += tmp_i;
		current = current->next;
	}
	buffer_to_return[total_buffer_len] = '\n';
	buffer_to_return[total_buffer_len + 1] = '\0';
	return (buffer_to_return);
}

/**
 * @param tmp a pointer to pointer to alter
 * @param fd file descriptor of a file or STDIN
 * @param total_buffer_len the buffer length returned until n
 * @brief Finds the new line and returns the total_buffer_len until n
 */
int	find_n(t_list **tmp, int fd, int total_buffer_len)
{
	ssize_t	size_read;
	int		pos_index;

	size_read = 0;
	pos_index = 0;
	while (find_new_line(*tmp) == -1)
	{
		total_buffer_len += BUFFER_SIZE;
		(*tmp)->next = malloc_new_t_list();
		*tmp = (*tmp)->next;
		size_read = read(fd, (*tmp)->content, BUFFER_SIZE);
		if (size_read < 0)
			return (-1);
		(*tmp)->content[size_read] = '\0';
	}
	pos_index = find_new_line(*tmp);
	total_buffer_len += pos_index;
	return (total_buffer_len);
}

/**
* @param list a pointer to pointer to alter
	directly the new head of the linked list
 * @param fd file descriptor of a file or STDIN
 * @brief Finds the new line and calls a function to return the buffer
 */
char	*find_n_return_buffer(t_list **list, int fd)
{
	int		total_buffer_len;
	int		pos_n;
	char	*buffer;
	t_list	*tmp;

	tmp = *list;
	total_buffer_len = 0;
	pos_n = 0;
	total_buffer_len = find_n(&tmp, fd, total_buffer_len);
	if (total_buffer_len == -1)
		return (NULL);
	buffer = append_buffer_until_n(*list, total_buffer_len);
	pos_n = find_new_line(tmp);
	free_memory_after_n_encountered(list, tmp, pos_n);
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

	buffer[0] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!head)
	{
		head = malloc_new_t_list();
		if (!head || read(fd, head->content, BUFFER_SIZE) <= 0)
			return (NULL);
	}
	buffer = find_n_return_buffer(&head, fd);
	return (buffer);
}

int	main(void)
{
	int		fd;
	char	*buffer;

	fd = open("arquivo.txt", O_RDONLY);
	buffer = get_next_line(fd);
	free(buffer);
	return (0);
}
// int main(void)
// {
//     int fd;
//     char *buffer;

//     // // Test 1: Single line with \n
//     // printf("Test 1 - Single line:");
//     // fd = open("test1.txt", O_RDONLY);
//     // while ((buffer = get_next_line(fd)))
//     // {
//     //     write(1, buffer, strlen(buffer)); // Use write to show \n
//     //     printf("\nLine length: %zu\n", strlen(buffer));
//     //     free(buffer);
//     // }
//     // close(fd);

//     // Test 2: Multiple lines
//     printf("\nTest 2 - Multiple lines:\n");
//     fd = open("test1.txt", O_RDONLY);
//     while ((buffer = get_next_line(fd)))
//     {
//         write(1, buffer, strlen(buffer));
//         printf("Line length: %zu\n", strlen(buffer));
//         free(buffer);
//     }
//     close(fd);

//     // // Test 3: No \n at end
//     // printf("\nTest 3 - No newline:\n");
//     // fd = open("test3.txt", O_RDONLY);
//     // while ((buffer = get_next_line(fd)))
//     // {
//     //     write(1, buffer, strlen(buffer));
//     //     printf("Line length: %zu\n", strlen(buffer));
//     //     free(buffer);
//     // }
//     // close(fd);

//     return (0);
// }
