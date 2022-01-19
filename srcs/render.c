/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 16:26:56 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: clear_buffer() is needed?
int	render(t_param *p)
{
	mlx_clear_window(p->mlx, p->win);
	raycasting(p);
	buffer_to_img(p->buf3D, p->img3D, SCREENWIDTH, \
									SCREENHEIGHT);
	clear_buffer(p->buf3D, SCREENWIDTH, SCREENHEIGHT);
	mlx_put_image_to_window(p->mlx, p->win, p->img3D.img, 0, 0);
	return (0);
}

void	draw_verline(int x, int drawstart, int drawend, int color, t_param *p)
{
	int	y;

	y = drawstart - 1;
	while (++y <= drawend)
	{
		if (y < 0 || y >= SCREENHEIGHT)
			continue ;
		p->buf3D[y][x] = color;
	}
}
