/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:11 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/17 23:07:35 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// int shift_buffer()
// {}

// o array e verifica se existe um caractere \n.
// o índice da posição do caractere ou um indicador de ausência (-1).
char *find_newline_in_buffer(char *buffer, int fd)
{
	ssize_t bytes_read;
	char	*buffer_to_concat;
	char	*tmp;

	bytes_read = 0;
	buffer_to_concat = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer_to_concat)
		return NULL;
	buffer_to_concat[0] = '\0';
	while (ft_strchr(buffer_to_concat, '\n') == 0)
	{
		bytes_read = read(fd, buffer_to_concat, BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		buffer_to_concat[bytes_read] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(buffer, buffer_to_concat);
		if (!buffer)
			return NULL;
	}
	return buffer;
}

char *get_next_line(int fd)
{
	static char *buffer[1024];
	// buffer = NULL;

	// if (!buffer)
	// {
	// 	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	// 	if (!buffer)
	// 		return NULL;
	// 	buffer = ft_memset(buffer, 0, BUFFER_SIZE);
	// }
	find_newline_in_buffer(buffer, fd);
	return (buffer);
}

int	main(void)
{
	int	fd;
	fd = open("arquivo.txt", O_RDONLY);

	// int i;
	// i = 0;
	get_next_line(fd);
	// while (buffer == (get_next_line(fd) != NULL))
	// {
	// 	printf("%s", buffer);
	// 	free(buffer);
	// }
	close(fd);
	return (0);
}
