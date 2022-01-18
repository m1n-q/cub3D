/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 17:56:24 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int render(t_param *p)	//Top level
{
	mlx_clear_window(p->mlx, p->win);
	draw_2Dmap(p);
	draw_2Dplayer(p);
	raycasting(p);
	draw_dir(p);
	// draw_verLine(5 * p->cfg->minimapscale - 2, 0, SCREENHEIGHT - 1, p->floor_color, p);
	buffer_to_img(p->buf2D, p->img2D, p->cfg->mapwidth * p->cfg->minimapscale, \
									p->cfg->mapheight * p->cfg->minimapscale);
	buffer_to_img(p->buf3D, p->img3D, SCREENWIDTH, \
									SCREENHEIGHT);
	// clear_buffer(p->buf2D);
	clear_buffer(p->buf3D, SCREENWIDTH, SCREENHEIGHT);	//NOTE: is needed?
	mlx_put_image_to_window(p->mlx, p->win, p->img3D.img, 0, 0);
	mlx_put_image_to_window(p->mlx, p->win, p->img2D.img, 0, 0);
	return (0);
}

void	draw_verLine(int x, int drawStart, int drawEnd, int color, t_param *p)
{
	for (int y = drawStart; y <= drawEnd; y++)
	{
		if (y < 0 || y >= SCREENHEIGHT)
			continue ;
		p->buf3D[y][x] = color;
	}
}
