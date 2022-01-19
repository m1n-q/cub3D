/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 19:14:01 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: clear_buffer() is needed?
int	render(t_param *p)
{
	mlx_clear_window(p->mlx, p->win);
	raycasting(p);
	buffer_to_img(p->buf3d, p->img3d, SCREENWIDTH, SCREENHEIGHT);
	clear_buffer(p->buf3d, SCREENWIDTH, SCREENHEIGHT);
	mlx_put_image_to_window(p->mlx, p->win, p->img3d.img, 0, 0);
	return (0);
}

void	draw_verline(t_param *p, t_drawinfo draw, int color, int mode)
{
	int	y;
	int	drawstart;
	int	drawend;

	if (mode == TOP)
	{
		drawstart = 0;
		drawend = draw.start_y;
	}
	else if (mode == BOTTOM)
	{
		drawstart = draw.end_y;
		drawend = SCREENHEIGHT - 1;
	}
	else
	{
		drawstart = draw.start_y;
		drawend = draw.end_y;
	}
	y = drawstart - 1;
	while (++y <= drawend)
	{
		if ((0 <= y) && (y < SCREENHEIGHT))
			p->buf3d[y][draw.x] = color;
	}
}
