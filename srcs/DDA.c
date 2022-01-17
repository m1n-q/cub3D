/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 23:58:41 by mishin            #+#    #+#             */
/*   Updated: 2022/01/17 21:01:39 by mishin           ###   ########.fr       */
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
		dist_vert = (P->pos.x - (int)P->pos.x) * D.delta_vert;
	else
		dist_vert = ((int)P->pos.x + 1 - P->pos.x) * D.delta_vert;
	if (D.raydir.y > 0)
		dist_horz = ((int)P->pos.y + 1 - P->pos.y) * D.delta_horz;
	else
		dist_horz = (P->pos.y - (int)P->pos.y) * D.delta_horz;
	return ((VECTOR){dist_vert, dist_horz});
}

DDA	get_DDA_info(PARAM *P, double r)
{
	DDA	D;

	D.hit = P->pos;
	D.raydir = get_raydir(P->dir, r);
	D.step = get_stepdir(D);
	D.delta_vert = sqrt(1 + pow((D.raydir.y / (D.raydir.x + 0.0001)), 2.0));
	D.delta_horz = sqrt(1 + pow((D.raydir.x / (D.raydir.y + 0.0001)), 2.0));
	D.dist_vert = get_dist_vh(P, D).x;
	D.dist_horz = get_dist_vh(P, D).y;
	return (D);
}

void	run_DDA(PARAM *P, DDA *D)
{
	int	hit;
	int	Scale;

	hit = 0;
	Scale = P->cfg->blockScale;
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
		if (P->worldMap[(int)(D->hit.y / Scale)][(int)(D->hit.x / Scale)] == 1)
			hit = 1;

		// printf("dist_vh => (%f, %f)\n", D->dist_vert, D->dist_horz);
		// printf("hit => (%f, %f)\n", D->hit.x, D->hit.y); scale 이 어디서 적용되고 있지?
	}
}
