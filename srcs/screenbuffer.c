/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenbuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:16:50 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 16:27:15 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_buffer(t_param *p)
{
	int	i;

	i = -1;
	while (++i < SCREENHEIGHT)
		free(p->buf3D[i]);
	free(p->buf3D);
}

void	clear_buffer(int **buffer, int w, int h)
{
	int	x;
	int	y;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			buffer[y][x] = 0;
	}
}
