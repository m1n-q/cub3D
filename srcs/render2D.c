/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:35:09 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:04:07 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ray(t_param *p, t_dda D)
{
	double	dX=0, dY=0;
	t_vector	minipos;
	t_vector	minihit;

	minipos.x = p->pos.x / p->cfg->blockscale * p->cfg->minimapscale;
	minipos.y = p->pos.y / p->cfg->blockscale * p->cfg->minimapscale;
	minihit.x = D.hit.x / p->cfg->blockscale * p->cfg->minimapscale;
	minihit.y = D.hit.y / p->cfg->blockscale * p->cfg->minimapscale;

	// printf("mpos = (%lf, %lf)\n", minipos.x, minipos.y);
	// printf("mhit = (%lf, %lf)\n", minihit.x, minihit.y);
	for (int linelength = 0; (minipos.x + dX > 0) && (p->pos.y + dY > 0) && (minipos.x + dX < p->cfg->mapwidth * p->cfg->minimapscale) && (minipos.y + dY < p->cfg->mapheight * p->cfg->minimapscale); linelength++)
	{
		dX += D.raydir.x;
		dY += D.raydir.y;
		if(!((minipos.x + dX > 0) && (minipos.y + dY > 0) && (minipos.x + dX < p->cfg->mapwidth * p->cfg->minimapscale) && (minipos.y + dY < p->cfg->mapheight * p->cfg->minimapscale)))
			break;


		if (D.side == 0)
		{
			if (minipos.x <= (minihit.x))
			{
				if (minipos.x + dX <= (minihit.x))
					p->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = 0x00ff00;
			}

			else if (minipos.x > (minihit.x))
			{
				if (minipos.x + dX >= (minihit.x))
					p->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = 0x00ff00;
			}
		}
		else if (D.side == 1)
		{
			if (minipos.y <= (minihit.y))
			{
				if (minipos.y + dY <= (minihit.y))
					p->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = 0x00ff00;
			}

			else if (minipos.y > (minihit.y))
			{
				if (minipos.y + dY >= (minihit.y))
					p->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = 0x00ff00;
			}
		}
	}
}

int	draw_2Dsquare(t_param *p, int x, int y, t_img img)
{
	for (int row = 0; row < p->cfg->minimapscale; row++)
		for (int col = 0; col < p->cfg->minimapscale; col++)
			p->buf2D[y * p->cfg->minimapscale + row][x * p->cfg->minimapscale + col] = img.addr[row * img.linesize / sizeof(int) + col];
	return (1);
}

void	draw_2Dmap(t_param *p)
{
	for (int y=0; y < p->cfg->mapheight; y++)
		for (int x=0; x < p->cfg->mapwidth; x++)
			if (draw_2Dsquare(p, x, y, p->grid) && p->worldmap[y][x])
				draw_2Dsquare(p, x, y, p->block);
}

void	draw_dir(t_param *p)
{
	double dX, dY; dX=0, dY=0;

	t_vector	minipos;
	minipos.x = p->pos.x / p->cfg->blockscale * p->cfg->minimapscale;
	minipos.y = p->pos.y / p->cfg->blockscale * p->cfg->minimapscale;

	for (int linelength = 0; linelength < p->cfg->minimapscale; linelength++)
	{
		dX += p->dir.x;
		dY += p->dir.y;
		p->buf2D[(int)(minipos.y + dY)][(int)(minipos.x + dX)] = 0xff0000;
	}
}


void	draw_2Dplayer(t_param *p)
{
	t_vector	minipos;
	minipos.x = p->pos.x / p->cfg->blockscale * p->cfg->minimapscale;
	minipos.y = p->pos.y / p->cfg->blockscale * p->cfg->minimapscale;

	for (int y = -2; y <= 0; y++)
		for (int x = -(y + 2); x <= (y + 2); x++)
			p->buf2D[(int)(minipos.y + (y))][(int)(minipos.x + (x))] = 0xff0000;
	for (int y = 0; y <= 2; y++)
		for (int x = (y - 2); x <= -(y - 2); x++)
			p->buf2D[(int)(minipos.y + (y))][(int)(minipos.x + (x))] = 0xff0000;

}
