/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:00:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 17:56:24 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_perp_dist(t_param *p, t_DDA *D)
{
	double	perp_delta;
	double	k;
	t_vector	perp_dir;

	perp_dir.x = cos(PI / 2) * p->dir.x - sin(PI / 2) * p->dir.y;
	perp_dir.y = sin(PI / 2) * p->dir.x + cos(PI / 2) * p->dir.y;
	perp_delta = ((perp_dir.y) / (perp_dir.x));
	k = p->pos.y - p->pos.x * perp_delta;										// constant for perpendicular linear
	D->perp_dist = fabs(perp_delta * D->hit.x - D->hit.y + k) / \
						sqrt(pow(perp_delta, 2.0) + 1);
}

void	get_draw_info(t_param *p, double perp_dist, t_drawinfo *draw)
{
	draw->length = (SCREENWIDTH) / perp_dist * p->cfg->blockscale;		// p->cfg->blockscale와 비례해야 함..!
	draw->start_y = SCREENHEIGHT / 2 - draw->length / 2;
	draw->end_y = SCREENHEIGHT / 2 + draw->length / 2;
	draw->x++;
	if (draw->x >= SCREENWIDTH)
			draw->x = SCREENWIDTH - 1;
}

int	raycasting(t_param *p)
{
	t_DDA			D;
	t_drawinfo	draw;
	double		angle;
	double		dr;
	double		r;

	draw.x = -1;
	angle = (PI / 6.0);
	dr = (angle * 2.0 / p->cfg->num_rays);
	r = -(angle);
	while (r <= angle)
	{
		D = get_DDA_info(p, r);
		run_DDA(p, &D);
		draw_ray(p, D);
		draw_2Dsquare(p, (int)(D.hit.x / p->cfg->blockscale), (int)(D.hit.y / p->cfg->blockscale), p->hblock);
		get_perp_dist(p, &D);
		get_draw_info(p, D.perp_dist, &draw);
		fill_by_texture(p, D, draw);
		draw_verLine(draw.x, 0, draw.start_y, p->ceili_color, p);
		draw_verLine(draw.x, draw.end_y, SCREENHEIGHT - 1, p->floor_color, p);
		r += dr;
	}
	return (0);
}
