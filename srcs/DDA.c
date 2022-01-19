/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 23:58:41 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 16:37:09 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	get_raydir(t_vector dir, double angle)
{
	t_vector	raydir;

	raydir.x = cos(angle) * dir.x - sin(angle) * dir.y;
	raydir.y = sin(angle) * dir.x + cos(angle) * dir.y;
	return (raydir);
}

t_vector	get_stepdir(t_dda __dda)
{
	t_vector	step;

	step.x = 1.0;
	step.y = 1.0;
	if (__dda.raydir.x < 0)
		step.x *= -1.0;
	if (__dda.raydir.y < 0)
		step.y *= -1.0;
	return (step);
}

t_vector	get_dist_vh(t_param *p, t_dda __dda)
{
	double	dist_vert;
	double	dist_horz;

	if (__dda.raydir.x < 0)
		dist_vert = (p->pos.x - (int)p->pos.x) * __dda.delta_vert;
	else
		dist_vert = ((int)p->pos.x + 1 - p->pos.x) * __dda.delta_vert;
	if (__dda.raydir.y > 0)
		dist_horz = ((int)p->pos.y + 1 - p->pos.y) * __dda.delta_horz;
	else
		dist_horz = (p->pos.y - (int)p->pos.y) * __dda.delta_horz;
	return ((t_vector){dist_vert, dist_horz});
}

t_dda	get_dda_info(t_param *p, double r)
{
	t_dda	__dda;

	__dda.hit = p->pos;
	__dda.raydir = get_raydir(p->dir, r);
	__dda.step = get_stepdir(__dda);
	__dda.delta_vert = \
			sqrt(1 + pow((__dda.raydir.y / (__dda.raydir.x + 0.0001)), 2.0));
	__dda.delta_horz = \
			sqrt(1 + pow((__dda.raydir.x / (__dda.raydir.y + 0.0001)), 2.0));
	__dda.dist_vert = get_dist_vh(p, __dda).x;
	__dda.dist_horz = get_dist_vh(p, __dda).y;
	return (__dda);
}

void	run_dda(t_param *p, t_dda *__dda)
{
	int	hit;
	int	scale;

	hit = 0;
	scale = p->cfg->blockscale;
	while (hit == 0)
	{
		if (__dda->dist_vert < __dda->dist_horz)
		{
			__dda->dist_vert += __dda->delta_vert;
			__dda->hit.x += __dda->step.x;
			__dda->side = VERT;
		}
		else
		{
			__dda->dist_horz += __dda->delta_horz;
			__dda->hit.y += __dda->step.y;
			__dda->side = HORZ;
		}
		if (p->worldmap[(int)(__dda->hit.y / scale)] \
						[(int)(__dda->hit.x / scale)] == 1)
			hit = 1;
	}
}
