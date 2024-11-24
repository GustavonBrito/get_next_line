/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:08 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/11/24 16:50:55 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# 	define BUFFER_SIZE 10
# endif

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
    char            *content;
    struct s_list   *next;
}   t_list;

t_list *malloc_new_t_list();
int     find_new_line(t_list *new_node);
char    *get_next_line(int fd);
char	*ft_strcat(char *dest, char *src);

#endif