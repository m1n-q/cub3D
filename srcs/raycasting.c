/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:00:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/17 19:45:47 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_perp_dist(PARAM *P, DDA *D)
{
	double	perp_delta;
	double	k;
	VECTOR	perp_dir;

	perp_dir.x = cos(PI / 2) * P->dir.x - sin(PI / 2) * P->dir.y;
	perp_dir.y = sin(PI / 2) * P->dir.x + cos(PI / 2) * P->dir.y;
	perp_delta = ((perp_dir.y) / (perp_dir.x));
	k = P->pos.y - P->pos.x * perp_delta;										// constant for perpendicular linear
	D->perp_dist = fabs(perp_delta * D->hit.x - D->hit.y + k) / \
						sqrt(pow(perp_delta, 2.0) + 1);
}

LINEDRAW	get_draw_info(PARAM *P, double perp_dist)
{
	LINEDRAW	draw;

	draw.length = (screenWidth) / perp_dist * P->cfg->blockScale;		// P->cfg->blockScale와 비례해야 함..!
	draw.start_y = screenHeight / 2 - draw.length / 2;
	draw.end_y = screenHeight / 2 + draw.length / 2;
	return (draw);
}

int	raycasting(PARAM *P)
{
	DDA			D;
	LINEDRAW	draw;
	double		angle;
	double		dr;
	double		r;

	LINEDRAW	prev;
	prev.x = 0;

	angle = (PI / 6.0);
	dr = (angle * 2.0 / P->cfg->NUM_RAYS);
	r = -(angle);
	while (r <= angle)
	{
		D = get_DDA_info(P, r);
		run_DDA(P, &D);
		draw_ray(P, D);
		draw_2Dsquare(P, (int)(D.hit.x / P->cfg->blockScale), (int)(D.hit.y / P->cfg->blockScale), P->hblock);
		get_perp_dist(P, &D);
		draw = get_draw_info(P, D.perp_dist);
		draw.x = ((r + angle) / dr);

		// if (abs(draw.x - prev.x) > 1)
		// {
		// 	// printf("draw.x = %d, prev.x = %d (%d)\n",draw.x, prev.x, 5 * P->cfg->minimapScale - 2);
		// 	printf("r = %f, dr = %f\n", r, dr);
		// 	prev.x += 1;
		// 	fill_by_texture(P, D, prev);
		// 	draw_verLine(prev.x, 0, prev.start_y, P->ceili_color, P);
		// 	draw_verLine(prev.x, prev.end_y, screenHeight - 1, P->floor_color, P);
		// }

		fill_by_texture(P, D, draw);
		draw_verLine(draw.x, 0, draw.start_y, P->ceili_color, P);
		draw_verLine(draw.x, draw.end_y, screenHeight - 1, P->floor_color, P);
		r += dr;

		prev = draw;
	}
	return (0);
}
