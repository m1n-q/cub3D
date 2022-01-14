/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 23:58:41 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 23:40:37 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

VECTOR	get_raydir(VECTOR dir, double angle)
{
	VECTOR	raydir;

	raydir.x = cos(angle) * dir.x - sin(angle) * dir.y;
	raydir.y = sin(angle) * dir.x + cos(angle) * dir.y;
	return (raydir);
}

VECTOR	get_stepdir(DDA D)
{
	VECTOR	step;

	step.x = 1.0;
	step.y = 1.0;
	if (D.raydir.x < 0)
		step.x *= -1.0;
	if (D.raydir.y < 0)
		step.y *= -1.0;
	return (step);
}

VECTOR	get_dist_vh(PARAM* P, DDA D)
{
	double	dist_vert;
	double	dist_horz;

	if (D.raydir.x < 0)
		dist_vert = (P->pos.x - (int)P->pos.x) * D.delta_vert / P->cfg->blockScale;
	else
		dist_vert = ((int)P->pos.x + P->cfg->blockScale - P->pos.x) * D.delta_vert / P->cfg->blockScale;
	if (D.raydir.y > 0)
		dist_horz = ((int)P->pos.y + P->cfg->blockScale - P->pos.y) * D.delta_horz / P->cfg->blockScale;
	else
		dist_horz = (P->pos.y - (int)P->pos.y) * D.delta_horz / P->cfg->blockScale;
	return ((VECTOR){dist_vert, dist_horz});
}

DDA	get_DDA_info(PARAM *P, double r)
{
	DDA	D;

	D.hit = P->pos;
	D.raydir = get_raydir(P->dir, r);
	D.step = get_stepdir(D);
	D.delta_vert = sqrt(1 + pow((D.raydir.y / (D.raydir.x + 0.0001)), 2.0)) * P->cfg->blockScale;
	D.delta_horz = sqrt(1 + pow((D.raydir.x / (D.raydir.y + 0.0001)), 2.0)) * P->cfg->blockScale;
	D.dist_vert = get_dist_vh(P, D).x;
	D.dist_horz = get_dist_vh(P, D).y;
	return (D);
}

void	run_DDA(PARAM *P, DDA *D)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (D->dist_vert < D->dist_horz)
		{
			D->dist_vert += D->delta_vert;
			D->hit.x += D->step.x;
			D->side = VERT;
		}
		else
		{
			D->dist_horz += D->delta_horz;
			D->hit.y += D->step.y;
			D->side = HORZ;
		}

		if (P->worldMap[(int)(D->hit.y / P->cfg->blockScale)][(int)(D->hit.x / P->cfg->blockScale)] > 0)
			hit = 1;
	}
	// printf("dda done\n");
}
