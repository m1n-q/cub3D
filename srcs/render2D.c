/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2022/01/13 21:30:16 by mishin           ###   ########.fr       */
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

void	draw_2Dmap(PARAM *P)
{
	for (int y=0; y < mapHeight; y++)
		for (int x=0; x < mapWidth; x++)
			if (draw_2Dsquare(P, x, y, P->grid) && worldMap[y][x])
				draw_2Dsquare(P, x, y, P->block);
}

void	draw_dir(PARAM *P)
{
	double dX, dY; dX=0, dY=0;

	for (int linelength = 0; linelength < 25; linelength++)
	{
		dX += P->dir.x;
		dY += P->dir.y;
		P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Red;
	}
}

void	draw_perpdir(PARAM *P, VECTOR perp_dir)
{
	for (double x = P->pos.x - perp_dir.x * 30, y = P->pos.y - perp_dir.y * 30; \
				x < P-> pos.x + perp_dir.x * 30; \
				x += perp_dir.x, y+= perp_dir.y)
			P->buf2D[(int)y][(int)x] = RGB_Yellow;
}

void	draw_2Dplayer(PARAM *P)
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
}

void	draw_2DCircle(PARAM *P)
{

	if (worldMap[(int)((int)P->pos.y / BLOCK_SIZE)][(int)((int)P->pos.x / BLOCK_SIZE)] == 0)
	{
		for (double r = 0.0; r <= PI * 2 ; r += 0.03)
		{
			double dX = 0.0, dY = 0.0;
			VECTOR newdir;

			newdir.x = cos(r) * P->dir.x - sin(r) * P->dir.y;
			newdir.y = sin(r) * P->dir.x + cos(r) * P->dir.y;
			for (int linelength = 0; linelength < collisionRange; linelength++)
			{
				dX += newdir.x;
				dY += newdir.y;
				if (worldMap[(int)((int)(P->pos.y + dY) / BLOCK_SIZE)][(int)((int)(P->pos.x + dX) / BLOCK_SIZE)])
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Yellow;
				else
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_White;
			}
		}
	}
}