/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:32:33 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 16:57:20 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rotate(int keycode, t_param *p)
{
	double	rot_angle;
	double	old_dirx;

	rot_angle = 0.2;
	old_dirx = p->dir.x;
	if (keycode == KEY_RIGHT)
	{
		p->dir.x = cos(rot_angle) * p->dir.x - sin(rot_angle) * p->dir.y;
		p->dir.y = sin(rot_angle) * old_dirx + cos(rot_angle) * p->dir.y;
	}
	else if (keycode == KEY_LEFT)
	{
		p->dir.x = cos(-rot_angle) * p->dir.x - sin(-rot_angle) * p->dir.y;
		p->dir.y = sin(-rot_angle) * old_dirx + cos(-rot_angle) * p->dir.y;
	}
	return (0);
}

static int	check_collision(t_param *p, double radius)
{
	double		r;
	t_vector	d;
	t_vector	newdir;
	int			linelength;
	int			scale;

	scale = p->cfg->blockscale;
	r = 0.0;
	while (r <= 2 * PI)
	{
		d = (t_vector){0.0, 0.0};
		newdir.x = cos(r) * p->dir.x - sin(r) * p->dir.y;
		newdir.y = sin(r) * p->dir.x + cos(r) * p->dir.y;
		linelength = 0;
		while (linelength < radius)
		{
			d = (t_vector){(d.x + newdir.x), (d.y + newdir.y)};
			if (p->worldmap[(int)((p->pos.y + d.y) / scale)] \
							[(int)((p->pos.x + d.x) / scale)])
				return (1);
			linelength++;
		}
		r += 0.03;
	}
	return (0);
}

static int	move_(t_param *p, t_vector movedir)
{
	double		amount;
	t_vector	oldpos;

	amount = p->cfg->blockscale / 10;
	oldpos = p->pos;
	p->pos.x += movedir.x * amount;
	if (check_collision(p, p->cfg->collision_range))
		p->pos = oldpos;
	oldpos = p->pos;
	p->pos.y += movedir.y * amount;
	if (check_collision(p, p->cfg->collision_range))
		p->pos = oldpos;
	return (0);
}

//NOTE: dir.x == 0 || dir.y == 0 일 때와 움직이는 양이 다른가...?
int	move(int keycode, t_param *p)
{
	t_vector	movedir;

	movedir.x = 0.0;
	movedir.y = 0.0;
	if (keycode == KEY_W)
	{
		movedir.x = p->dir.x;
		movedir.y = p->dir.y;
	}
	else if (keycode == KEY_S)
	{
		movedir.x = -(p->dir.x);
		movedir.y = -(p->dir.y);
	}
	else if (keycode == KEY_A)
	{
		movedir.x = (cos(-PI / 2) * p->dir.x - sin(-PI / 2) * p->dir.y);
		movedir.y = (sin(-PI / 2) * p->dir.x + cos(-PI / 2) * p->dir.y);
	}
	else if (keycode == KEY_D)
	{
		movedir.x = (cos(PI / 2) * p->dir.x - sin(PI / 2) * p->dir.y);
		movedir.y = (sin(PI / 2) * p->dir.x + cos(PI / 2) * p->dir.y);
	}
	return (move_(p, movedir));
}

int	quit(int keycode, t_param *p)
{
	if (keycode != KEY_ESC)
		return (1);
	bye(p);
	return (0);
}
