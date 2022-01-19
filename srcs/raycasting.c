/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:00:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 16:48:25 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_perp_dist(t_param *p, t_dda *__dda)
{
	double		perp_delta;
	double		k;
	t_vector	perp_dir;

	perp_dir.x = cos(PI / 2) * p->dir.x - sin(PI / 2) * p->dir.y;
	perp_dir.y = sin(PI / 2) * p->dir.x + cos(PI / 2) * p->dir.y;
	perp_delta = ((perp_dir.y) / (perp_dir.x));
	k = p->pos.y - p->pos.x * perp_delta;
	__dda->perp_dist = fabs(perp_delta * __dda->hit.x - __dda->hit.y + k) / \
							sqrt(pow(perp_delta, 2.0) + 1);
}

void	get_draw_info(t_param *p, double perp_dist, t_drawinfo *draw)
{
	draw->length = (SCREENWIDTH) / perp_dist * p->cfg->blockscale;
	draw->start_y = SCREENHEIGHT / 2 - draw->length / 2;
	draw->end_y = SCREENHEIGHT / 2 + draw->length / 2;
	draw->x++;
	if (draw->x >= SCREENWIDTH)
		draw->x = SCREENWIDTH - 1;
}

int	raycasting(t_param *p)
{
	t_dda		__dda;
	t_drawinfo	draw;
	double		angle;
	double		dr;
	double		r;

	draw.x = -1;
	angle = (PI / 6.0);
	dr = (angle * 2.0 / NUM_RAYS);
	r = -(angle);
	while (r <= angle)
	{
		__dda = get_dda_info(p, r);
		run_dda(p, &__dda);
		get_perp_dist(p, &__dda);
		get_draw_info(p, __dda.perp_dist, &draw);
		fill_by_texture(p, __dda, draw);
		draw_verline(p, draw, p->ceili_color, TOP);
		draw_verline(p, draw, p->floor_color, BOTTOM);
		r += dr;
	}
	return (0);
}
