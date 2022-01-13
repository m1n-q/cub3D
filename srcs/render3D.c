/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2022/01/13 20:44:34 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int render(PARAM *P)	//Top level
{
	mlx_clear_window(P->mlx, P->win);
	draw_2Dmap(P);
	draw_2Dplayer(P);
	draw_2DCircle(P);
	raycasting(P);

	draw_dir(P);
	buffer_to_img(P->buf2D, P->img2D, screenWidth, screenHeight);
	buffer_to_img(P->buf3D, P->img3D, screenWidth, screenHeight);
	// clear_buffer(P->buf2D);
	// clear_buffer(P->buf3D);	//NOTE: is needed?
	mlx_put_image_to_window(P->mlx, P->win, P->img2D.img, 0, 0);
	mlx_put_image_to_window(P->mlx, P->win, P->img3D.img, screenWidth, 0);

	return (0);
}

void	draw_verLine(int x, int drawStart, int drawEnd, int color, PARAM *P)
{
	for (int x2 = x; x2 < x + SCALE; x2++)
	{
		for (int y = drawStart; y <= drawEnd; y++)
		{
			if (y < 0 || y >= screenHeight)
				continue ;
			P->buf3D[y][x2] = color;
		}
	}
}

