/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:11 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/18 23:54:57 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char *extract_line(char **buffer)
{
	char	*new_line;
	char	*line;
	int		line_length;

	if (*buffer == NULL)
		return NULL;
	line_length = 0;
	new_line = ft_strchr(*buffer, '\n');
	line_length = new_line - *buffer + 1;
	line = malloc(sizeof(char) * line_length + 1);
	if (!line)
		return NULL;
	ft_strlcpy(line, *buffer, line_length + 1);
	ft_strlcpy(*buffer, new_line + 1, ft_strlen(new_line + 1) + 1);
	return line;
}

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
		{
			free(buffer);
			break;
		}
		free(tmp);
	}
	free(buffer_to_concat);
	return buffer;
}

char *get_next_line(int fd)
{
	static char *buffer;
	char		*buffer_to_return;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
		{
			free(buffer);
			return NULL;
		}
	}
	buffer = find_newline_in_buffer(buffer, fd);
	
	buffer_to_return = extract_line(&buffer);
	
	return (buffer_to_return);
}

int	main(void)
{
	int	fd;
	char *buffer;	
	fd = open("arquivo.txt", O_RDONLY);

	// int i;
	// i = 0;
	buffer = get_next_line(fd);
	//printf("%s", buffer);
	free(buffer);
	// while (buffer == (get_next_line(fd) != NULL))
	// {
	// 	printf("%s", buffer);
	// 	free(buffer);
	// }
	close(fd);
	return (0);
}
