/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:20:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 00:02:34 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	copy_and_append(char *prev, char *line, char *buf, ssize_t size)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	if (prev)
	{
		i = -1;
		while (prev[++i])
		{
			line[i] = prev[i];
		}
	}
	free(prev);
	j = -1;
	while (++j < size)
	{
		if (buf[j] == '\n')
			return ;
		line[i + j] = buf[j];
	}
	return ;
}

void	save_rmd(t_fd_set *set, char *buf, int idx_n, ssize_t size)
{
	ssize_t	i;
	ssize_t	j;

	if (idx_n + 1 == BUFFER_SIZE)
	{
		buffer_clear(set);
		return ;
	}
	i = idx_n;
	j = -1;
	while (++i < size)
	{
		set->rmd_buf[++j] = buf[i];
	}
	while (++j < BUFFER_SIZE)
	{
		set->rmd_buf[j] = 0;
	}
	set->rmd_len = ft_strlen(set->rmd_buf);
}

int	check_rmd(t_fd_set *set, char **line, char **prev)
{
	ssize_t	idx_n;

	idx_n = find_nl(set->rmd_buf);
	if (idx_n != BUFFER_SIZE)
	{
		*line = (char *)ft_calloc(idx_n + 1, 1);
		ft_memmove(*line, set->rmd_buf, idx_n);
		save_rmd(set, set->rmd_buf, idx_n, BUFFER_SIZE);
		return (1);
	}
	*line = (char *)ft_calloc(set->rmd_len + 1, 1);
	ft_memmove(*line, set->rmd_buf, set->rmd_len);
	*prev = *line;
	return (0);
}

int	read_line(t_fd_set *arr, int fd, char **line, char *buf)
{
	ssize_t	size;
	ssize_t	idx_n;
	char	*prev;

	if (check_rmd(&arr[fd], line, &prev))
		return (1);
	while (1)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
			return (-1);
		if (!size)
			return (buffer_clear(&arr[fd]));
		idx_n = find_nl(buf);
		if (idx_n < BUFFER_SIZE)
		{
			*line = (char *)ft_calloc(ft_strlen(prev) + (idx_n) + 1, 1);
			copy_and_append(prev, *line, buf, size);
			save_rmd(&arr[fd], buf, idx_n, size);
			return (1);
		}
		*line = (char *)ft_calloc(ft_strlen(prev) + size + 1, 1);
		copy_and_append(prev, *line, buf, size);
		prev = *line;
	}
}

int	get_next_line(int fd, char **line)
{
	static t_fd_set	arr[1025];
	char			*buf;
	int				ret;
	ssize_t			tmp;

	tmp = read(fd, NULL, 0);
	if (tmp < 0 || !line)
		return (-1);
	buf = (char *)ft_calloc(BUFFER_SIZE, 1);
	if (!buf)
		return (-1);
	if (!(arr[fd].was_called))
	{
		arr[fd].fd = fd;
		arr[fd].was_called = 1;
	}
	ret = read_line(arr, fd, line, buf);
	if (ret == -1)
		*line = NULL;
	free(buf);
	return (ret);
}
