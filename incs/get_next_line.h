/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:21:35 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 17:29:15 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define BUFFER_SIZE 1024

typedef struct s_fd_set
{
	int			was_called;
	int			fd;
	int			rmd_len;
	char		rmd_buf[BUFFER_SIZE];

}				t_fd_set;

ssize_t			find_nl(char *buf);
int				buffer_clear(t_fd_set *set);

void			copy_and_append(char *prev, char *line, \
								char *buf, ssize_t size);
void			save_rmd(t_fd_set *set, char *buf, int idx_n, ssize_t size);
int				check_rmd(t_fd_set *set, char **line, char **prev);
int				read_line(t_fd_set *arr, int fd, char **line, char *buf);
int				get_next_line(int fd, char **line);

#endif
