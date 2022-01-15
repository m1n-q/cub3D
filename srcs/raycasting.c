/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:00:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/15 19:28:55 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_perp_dist(PARAM *P, DDA *D)
{
	double	perp_delta;
	double	k;
	VECTOR	perp_dir;

	perp_dir.x		= cos(PI / 2) * P->dir.x - sin(PI / 2) * P->dir.y;
	perp_dir.y		= sin(PI / 2) * P->dir.x + cos(PI / 2) * P->dir.y;
	perp_delta		= ((perp_dir.y) / (perp_dir.x));
	k 				= P->pos.y - P->pos.x * perp_delta;						// constant for perpendicular linear
	D->perp_dist	= fabs(perp_delta * D->hit.x - D->hit.y + k) / sqrt(pow(perp_delta, 2.0) + 1);

	// draw_perpdir(P, perp_dir);
}

LINEDRAW	get_draw_info(PARAM *P, double perp_dist)
{
	LINEDRAW	draw;

	draw.length		= (double)(P->cfg->screenWidth) / perp_dist * P->cfg->blockScale;		// P->cfg->blockScale와 비례해야 함..!
	draw.start_y	= P->cfg->screenHeight / 2 - draw.length / 2;
	draw.end_y		= P->cfg->screenHeight / 2 + draw.length / 2;

	return (draw);
}

int	raycasting(PARAM *P)
{
	DDA			D;
	VECTOR		texpos;
	LINEDRAW	draw;
	double		angle = (PI / 6);
	double		dr = (angle * 2.0 / P->cfg->NUM_RAYS);

	for (double r = -angle; r <= angle; r+=dr)
	{
		D = get_DDA_info(P, r);
		run_DDA(P, &D);

		// draw hit block on 2Dmap
		draw_ray(P, D);
		draw_2Dsquare(P, (int)(D.hit.x / P->cfg->blockScale), (int)(D.hit.y / P->cfg->blockScale), P->hblock);

		// Calculate height of line to draw on screen
		get_perp_dist(P, &D);
		draw	= get_draw_info(P, D.perp_dist);
		draw.x	= (((r + (PI / 6)) / dr) * P->cfg->SCALE);		// draw starting X (pixel)

		texpos	= get_texture_pos(P, D);
		fill_by_texture(P, D, texpos, draw);

		draw_verLine(draw.x, 0, draw.start_y, 0x000044, P);
		draw_verLine(draw.x, draw.end_y, P->cfg->screenHeight - 1, 0x446600, P);
	}

	return (0);
}
