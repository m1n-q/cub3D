/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 23:58:41 by mishin            #+#    #+#             */
/*   Updated: 2022/01/11 11:08:33 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

VECTOR	get_raydir(VECTOR dir, double angle)
{
	VECTOR	raydir;

	raydir.x = cos(angle) * dir.x  - sin(angle) * dir.y;
	raydir.y = sin(angle) * dir.x  + cos(angle) * dir.y;

	return (raydir);
}

VECTOR	get_stepdir(VECTOR pos, DDA D)
{
	VECTOR	step;

	if (D.raydir.x < 0)	step.x = -1.0;
	else				step.x = 1.0;

	if (D.raydir.y > 0)	step.y = 1.0;
	else				step.y = -1.0;

	return (step);
}

VECTOR	get_dist_vh(VECTOR pos, DDA D)
{
	double	dist_vert;
	double	dist_horz;

	if (D.raydir.x < 0)	dist_vert = (pos.x - (int)pos.x) * D.delta_vert / BLOCK_SIZE;
	else				dist_vert = ((int)pos.x + BLOCK_SIZE - pos.x) * D.delta_vert / BLOCK_SIZE;


	if (D.raydir.y > 0)	dist_horz = ((int)pos.y + BLOCK_SIZE - pos.y) * D.delta_horz / BLOCK_SIZE;
	else				dist_horz = (pos.y - (int)pos.y) * D.delta_horz / BLOCK_SIZE;

	return ((VECTOR){dist_vert, dist_horz});
}

DDA	get_DDA_info(VECTOR pos, VECTOR dir, double r)
{
	DDA	D;

	D.hit			= pos;
	D.raydir		= get_raydir(dir, r);
	D.delta_vert	= sqrt(1 + pow(D.raydir.y, 2.0) / (pow(D.raydir.x + 0.0001, 2.0))) * BLOCK_SIZE;
	D.delta_horz	= sqrt(1 + pow(D.raydir.x, 2.0) / (pow(D.raydir.y + 0.0001, 2.0))) * BLOCK_SIZE;

	// check step direction
	D.step			= get_stepdir(pos, D);
	D.dist_vert		= get_dist_vh(pos, D).x;
	D.dist_horz		= get_dist_vh(pos, D).y;

	return (D);
}

void	run_DDA(DDA *D)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (D->dist_vert < D->dist_horz)
		{
			D->dist_vert	+= D->delta_vert;
			D->hit.x		+= D->step.x;
			D->side			= VERT;
		}
		else
		{
			D->dist_horz	+= D->delta_horz;
			D->hit.y		+= D->step.y;
			D->side			= HORZ;
		}

		// Check if ray has hit a wall
		if (worldMap[(int)(D->hit.y / BLOCK_SIZE)][(int)(D->hit.x / BLOCK_SIZE)] > 0)
			hit = 1;
	}
}
