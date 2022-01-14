/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:20:57 by mishin            #+#    #+#             */
/*   Updated: 2022/01/15 02:02:35 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	find_nl(char *buf)
{
	ssize_t	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		if (buf[i] == '\n')
			return (i);
	return (BUFFER_SIZE);
}

int		buffer_clear(t_fd_set *set)
{
	ssize_t	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		set->rmd_buf[i] = 0;
	set->rmd_len = 0;
	return (0);
}
