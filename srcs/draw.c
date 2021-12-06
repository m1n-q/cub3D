/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2021/12/06 20:04:35 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ray(PARAM *P, DDA D)
{
	double	dX=0, dY=0;
	for (int linelength = 0; (P->pos.x + dX > 0) && (P->pos.y + dY > 0) && (P->pos.x + dX < screenWidth) && (P->pos.y + dY < screenHeight); linelength++)
	{
		dX += D.raydir.x;
		dY += D.raydir.y;
		if(!((P->pos.x + dX > 0) && (P->pos.y + dY > 0) && (P->pos.x + dX < screenWidth) && (P->pos.y + dY < screenHeight)))
			break;


		if (D.side == 0)
		{
			if (P->pos.x <= (D.hit.x))
			{
				if (P->pos.x + dX <= (D.hit.x))
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Green;
			}

			else if (P->pos.x > (D.hit.x))
			{
				if (P->pos.x + dX >= (D.hit.x))
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Green;
			}
		}
		else if (D.side == 1)
		{
			if (P->pos.y <= (D.hit.y))
			{
				if (P->pos.y + dY <= (D.hit.y))
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Green;
			}

			else if (P->pos.y > (D.hit.y))
			{
				if (P->pos.y + dY >= (D.hit.y))
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Green;
			}
		}
	}
}

int	draw_2Dsquare(PARAM *P, int x, int y, IMG img)
{

	for (int row = 0; row < BLOCK_SIZE; row++)
		for (int col = 0; col < BLOCK_SIZE; col++)
			P->buf2D[y * BLOCK_SIZE + row][x * BLOCK_SIZE + col] = img.addr[row * img.linesize / sizeof(int) + col];
	return (1);
}

int	draw_2Dmap(PARAM *P)
{
	for (int y=0; y < mapHeight; y++)
		for (int x=0; x < mapWidth; x++)
			if (draw_2Dsquare(P, x, y, P->grid) && worldMap[y][x])
				draw_2Dsquare(P, x, y, P->block);


	return (0);
}

int	draw_dir(PARAM *P)
{
	double dX, dY; dX=0, dY=0;

	for (int linelength = 0; linelength < 25; linelength++)
	{
		dX += P->dir.x;
		dY += P->dir.y;
		P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Red;
		// mlx_put_image_to_window(P->mlx, P->win, P->pixel.yellow.img, P->pos.x + dX,  P->pos.y + dY);
	}
	return (0);
}

int	draw_perpdir(PARAM *P, VECTOR perp_dir)
{
	for (double x = P->pos.x - perp_dir.x * 30, y = P->pos.y - perp_dir.y * 30; \
					x < P-> pos.x + perp_dir.x * 30; \
					x += perp_dir.x, y+= perp_dir.y)
			P->buf2D[(int)y][(int)x] = RGB_Yellow;
	return (0);
}

int	draw_2Dplayer(PARAM *P)
{

	if (worldMap[(int)((int)P->pos.y / BLOCK_SIZE)][(int)((int)P->pos.x / BLOCK_SIZE)] == 0)
	{
		for (int y = -4; y <= 0; y++)
			for (int x = -(y + 4); x <= (y + 4); x++)
				P->buf2D[(int)(P->pos.y + (y))][(int)(P->pos.x + (x))] = RGB_Red;
		for (int y = 0; y <= 4; y++)
			for (int x = (y - 4); x <= -(y - 4); x++)
				P->buf2D[(int)(P->pos.y + (y))][(int)(P->pos.x + (x))] = RGB_Red;
	}

	return (0);
}


//FIXME: 벽과 정면일때 (perp), 벽 높이가 고정 : (385, 300) to (480, xxx) 의 거리가 (180)이 나오넹.
//FIXME: 멀리있을때, 왜곡이 심하고 비율이 이상함..
//FIXME: border를 지나는 경우 광선이 벽뚫음
int render(PARAM *P)
{
	// printf("pos = (%lf, %lf)\n", P->pos.x, P->pos.y);
	mlx_clear_window(P->mlx, P->win);
	draw_2Dmap(P);
	draw_2Dplayer(P);
	check_hit(P);

	draw_dir(P);
	buffer_to_img(P, P->buf2D, P->img2D, screenWidth, screenHeight);
	buffer_to_img(P, P->buf3D, P->img3D, screenWidth, screenHeight);
	clear_buffer(P, P->buf2D);
	clear_buffer(P, P->buf3D);
	mlx_put_image_to_window(P->mlx, P->win, P->img2D.img, 0, 0);
	mlx_put_image_to_window(P->mlx, P->win, P->img3D.img, screenWidth, 0);

	// test wall texture
	// for (int row = 0; row < texWidth; row++)
	// 	for (int col = 0; col < texWidth; col++)
	// 		P->buf2D[row][col] = P->texture[0][row * texWidth + col];
	// buffer_to_img(P, P->buf2D, P->img2D, texWidth, texHeight);
  	// mlx_put_image_to_window(P->mlx, P->win, P->img2D.img, 0, 0);
	return (0);
}
