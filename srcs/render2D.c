/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 17:08:17 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ray(PARAM *P, DDA D)
{
	double	dX=0, dY=0;
	VECTOR	minipos;
	VECTOR	minihit;

	minipos.x = P->pos.x / blockScale * minimapScale;
	minipos.y = P->pos.y / blockScale * minimapScale;
	minihit.x = D.hit.x / blockScale * minimapScale;
	minihit.y = D.hit.y / blockScale * minimapScale;

	// printf("mpos = (%lf, %lf)\n", minipos.x, minipos.y);
	// printf("mhit = (%lf, %lf)\n", minihit.x, minihit.y);
	for (int linelength = 0; (minipos.x + dX > 0) && (P->pos.y + dY > 0) && (minipos.x + dX < mapWidth * minimapScale) && (minipos.y + dY < mapHeight * minimapScale); linelength++)
	{
		dX += D.raydir.x;
		dY += D.raydir.y;
		if(!((minipos.x + dX > 0) && (minipos.y + dY > 0) && (minipos.x + dX < mapWidth * minimapScale) && (minipos.y + dY < mapHeight * minimapScale)))
			break;


		if (D.side == 0)
		{
			if (minipos.x <= (minihit.x))
			{
				if (minipos.x + dX <= (minihit.x))
					P->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = RGB_Green;
			}

			else if (minipos.x > (minihit.x))
			{
				if (minipos.x + dX >= (minihit.x))
					P->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = RGB_Green;
			}
		}
		else if (D.side == 1)
		{
			if (minipos.y <= (minihit.y))
			{
				if (minipos.y + dY <= (minihit.y))
					P->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = RGB_Green;
			}

			else if (minipos.y > (minihit.y))
			{
				if (minipos.y + dY >= (minihit.y))
					P->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = RGB_Green;
			}
		}
	}
}

int	draw_2Dsquare(PARAM *P, int x, int y, IMG img)
{
	for (int row = 0; row < minimapScale; row++)
		for (int col = 0; col < minimapScale; col++)
			P->buf2D[y * minimapScale + row][x * minimapScale + col] = img.addr[row * img.linesize / sizeof(int) + col];
	return (1);
}

void	draw_2Dmap(PARAM *P)
{
	for (int y=0; y < mapHeight; y++)
		for (int x=0; x < mapWidth; x++)
			if (draw_2Dsquare(P, x, y, P->grid) && P->worldMap[y][x])
				draw_2Dsquare(P, x, y, P->block);
}

void	draw_dir(PARAM *P)
{
	double dX, dY; dX=0, dY=0;

	VECTOR	minipos;
	minipos.x = P->pos.x / blockScale * minimapScale;
	minipos.y = P->pos.y / blockScale * minimapScale;

	for (int linelength = 0; linelength < minimapScale; linelength++)
	{
		dX += P->dir.x;
		dY += P->dir.y;
		P->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = RGB_Red;
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
	VECTOR	minipos;
	minipos.x = P->pos.x / blockScale * minimapScale;
	minipos.y = P->pos.y / blockScale * minimapScale;

	for (int y = -2; y <= 0; y++)
		for (int x = -(y + 2); x <= (y + 2); x++)
			P->buf2D[(int)(minipos.y + (y))][(int)(minipos.x + (x))] = RGB_Red;
	for (int y = 0; y <= 2; y++)
		for (int x = (y - 2); x <= -(y - 2); x++)
			P->buf2D[(int)(minipos.y + (y))][(int)(minipos.x + (x))] = RGB_Red;

}

void	draw_2DCircle(PARAM *P)
{

	if (P->worldMap[(int)((int)P->pos.y / blockScale)][(int)((int)P->pos.x / blockScale)] == 0)
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
				if (P->worldMap[(int)((int)(P->pos.y + dY) / blockScale)][(int)((int)(P->pos.x + dX) / blockScale)])
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Yellow;
				else
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_White;
			}
		}
	}
}
