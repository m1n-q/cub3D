/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:00:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 16:56:18 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_perp_dist(t_param *P, t_DDA *D)
{
	double	perp_delta;
	double	k;
	t_vector	perp_dir;

	perp_dir.x = cos(PI / 2) * P->dir.x - sin(PI / 2) * P->dir.y;
	perp_dir.y = sin(PI / 2) * P->dir.x + cos(PI / 2) * P->dir.y;
	perp_delta = ((perp_dir.y) / (perp_dir.x));
	k = P->pos.y - P->pos.x * perp_delta;										// constant for perpendicular linear
	D->perp_dist = fabs(perp_delta * D->hit.x - D->hit.y + k) / \
						sqrt(pow(perp_delta, 2.0) + 1);
}

void	get_draw_info(t_param *P, double perp_dist, t_drawinfo *draw)
{
	draw->length = (screenWidth) / perp_dist * P->cfg->blockscale;		// P->cfg->blockscale와 비례해야 함..!
	draw->start_y = screenHeight / 2 - draw->length / 2;
	draw->end_y = screenHeight / 2 + draw->length / 2;
	draw->x++;
	if (draw->x >= screenWidth)
			draw->x = screenWidth - 1;
}

int	raycasting(t_param *P)
{
	t_DDA			D;
	t_drawinfo	draw;
	double		angle;
	double		dr;
	double		r;

	draw.x = -1;
	angle = (PI / 6.0);
	dr = (angle * 2.0 / P->cfg->num_rays);
	r = -(angle);
	while (r <= angle)
	{
		D = get_DDA_info(P, r);
		run_DDA(P, &D);
		draw_ray(P, D);
		draw_2Dsquare(P, (int)(D.hit.x / P->cfg->blockscale), (int)(D.hit.y / P->cfg->blockscale), P->hblock);
		get_perp_dist(P, &D);
		get_draw_info(P, D.perp_dist, &draw);
		fill_by_texture(P, D, draw);
		draw_verLine(draw.x, 0, draw.start_y, P->ceili_color, P);
		draw_verLine(draw.x, draw.end_y, screenHeight - 1, P->floor_color, P);
		r += dr;
	}
	return (0);
}
