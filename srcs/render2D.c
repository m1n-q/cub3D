/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 16:57:50 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ray(t_param *P, t_DDA D)
{
	double	dX=0, dY=0;
	t_vector	minipos;
	t_vector	minihit;

	minipos.x = P->pos.x / P->cfg->blockscale * P->cfg->minimapscale;
	minipos.y = P->pos.y / P->cfg->blockscale * P->cfg->minimapscale;
	minihit.x = D.hit.x / P->cfg->blockscale * P->cfg->minimapscale;
	minihit.y = D.hit.y / P->cfg->blockscale * P->cfg->minimapscale;

	// printf("mpos = (%lf, %lf)\n", minipos.x, minipos.y);
	// printf("mhit = (%lf, %lf)\n", minihit.x, minihit.y);
	for (int linelength = 0; (minipos.x + dX > 0) && (P->pos.y + dY > 0) && (minipos.x + dX < P->cfg->mapwidth * P->cfg->minimapscale) && (minipos.y + dY < P->cfg->mapheight * P->cfg->minimapscale); linelength++)
	{
		dX += D.raydir.x;
		dY += D.raydir.y;
		if(!((minipos.x + dX > 0) && (minipos.y + dY > 0) && (minipos.x + dX < P->cfg->mapwidth * P->cfg->minimapscale) && (minipos.y + dY < P->cfg->mapheight * P->cfg->minimapscale)))
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

int	draw_2Dsquare(t_param *P, int x, int y, t_img img)
{
	for (int row = 0; row < P->cfg->minimapscale; row++)
		for (int col = 0; col < P->cfg->minimapscale; col++)
			P->buf2D[y * P->cfg->minimapscale + row][x * P->cfg->minimapscale + col] = img.addr[row * img.linesize / sizeof(int) + col];
	return (1);
}

void	draw_2Dmap(t_param *P)
{
	for (int y=0; y < P->cfg->mapheight; y++)
		for (int x=0; x < P->cfg->mapwidth; x++)
			if (draw_2Dsquare(P, x, y, P->grid) && P->worldmap[y][x])
				draw_2Dsquare(P, x, y, P->block);
}

void	draw_dir(t_param *P)
{
	double dX, dY; dX=0, dY=0;

	t_vector	minipos;
	minipos.x = P->pos.x / P->cfg->blockscale * P->cfg->minimapscale;
	minipos.y = P->pos.y / P->cfg->blockscale * P->cfg->minimapscale;

	for (int linelength = 0; linelength < P->cfg->minimapscale; linelength++)
	{
		dX += P->dir.x;
		dY += P->dir.y;
		P->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = RGB_Red;
	}
}

void	draw_perpdir(t_param *P, t_vector perp_dir)
{
	for (double x = P->pos.x - perp_dir.x * 30, y = P->pos.y - perp_dir.y * 30; \
				x < P-> pos.x + perp_dir.x * 30; \
				x += perp_dir.x, y+= perp_dir.y)
			P->buf2D[(int)y][(int)x] = RGB_Yellow;
}

void	draw_2Dplayer(t_param *P)
{
	t_vector	minipos;
	minipos.x = P->pos.x / P->cfg->blockscale * P->cfg->minimapscale;
	minipos.y = P->pos.y / P->cfg->blockscale * P->cfg->minimapscale;

	for (int y = -2; y <= 0; y++)
		for (int x = -(y + 2); x <= (y + 2); x++)
			P->buf2D[(int)(minipos.y + (y))][(int)(minipos.x + (x))] = RGB_Red;
	for (int y = 0; y <= 2; y++)
		for (int x = (y - 2); x <= -(y - 2); x++)
			P->buf2D[(int)(minipos.y + (y))][(int)(minipos.x + (x))] = RGB_Red;

}

void	draw_2DCircle(t_param *P)
{

	if (P->worldmap[(int)((int)P->pos.y / P->cfg->blockscale)][(int)((int)P->pos.x / P->cfg->blockscale)] == 0)
	{
		for (double r = 0.0; r <= PI * 2 ; r += 0.03)
		{
			double dX = 0.0, dY = 0.0;
			t_vector newdir;

			newdir.x = cos(r) * P->dir.x - sin(r) * P->dir.y;
			newdir.y = sin(r) * P->dir.x + cos(r) * P->dir.y;
			for (int linelength = 0; linelength < P->cfg->collision_range; linelength++)
			{
				dX += newdir.x;
				dY += newdir.y;
				if (P->worldmap[(int)((int)(P->pos.y + dY) / P->cfg->blockscale)][(int)((int)(P->pos.x + dX) / P->cfg->blockscale)])
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_Yellow;
				else
					P->buf2D[(int)(P->pos.y + dY)][(int)(P->pos.x + dX)] = RGB_White;
			}
		}
	}
}
