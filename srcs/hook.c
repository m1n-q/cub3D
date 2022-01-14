/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:13:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 17:08:17 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rotate(int keycode, PARAM *P)
{
	double	rot_angle;
	double	old_dirx;

	rot_angle = 0.2;
	old_dirx = P->dir.x;
	if (keycode == KEY_RIGHT)
	{
		P->dir.x = cos(rot_angle) * P->dir.x - sin(rot_angle) * P->dir.y;
		P->dir.y = sin(rot_angle) * old_dirx + cos(rot_angle) * P->dir.y;
	}
	else if (keycode == KEY_LEFT)
	{
		P->dir.x = cos(-rot_angle) * P->dir.x - sin(-rot_angle) * P->dir.y;
		P->dir.y = sin(-rot_angle) * old_dirx + cos(-rot_angle) * P->dir.y;
	}
	return (0);
}

int	checkCollision(PARAM *P, double radius)
{
	double	r;
	VECTOR	d;
	VECTOR	newdir;
	int		linelength;

	r = 0.0;
	while (r <= 2 * PI)
	{
		d.x = 0.0;
		d.y = 0.0;
		newdir.x = cos(r) * P->dir.x - sin(r) * P->dir.y;
		newdir.y = sin(r) * P->dir.x + cos(r) * P->dir.y;
		linelength = 0;
		while (linelength < radius)
		{
			d.x += newdir.x;
			d.y += newdir.y;
			if (worldMap[(int)((int)(P->pos.y + d.y) / blockScale)][(int)((int)(P->pos.x + d.x) / blockScale)])
				return (1);
			linelength++;
		}
		r += 0.03;
	}
	return (0);
}

int	move_(PARAM *P, VECTOR movedir)
{
	int		amount;
	VECTOR	oldpos;

	amount = 5;
	oldpos = P->pos;
	P->pos.x += movedir.x * amount;
	if (checkCollision(P, collisionRange))
		P->pos = oldpos;
	oldpos = P->pos;
	P->pos.y += movedir.y * amount;
	if (checkCollision(P, collisionRange))
		P->pos = oldpos;
	return (0);
}

//NOTE: dir.x == 0 || dir.y == 0 일 때와 움직이는 양이 다른가...?
int	move(int keycode, PARAM *P)
{
	VECTOR	movedir;

	movedir.x = 0.0;
	movedir.y = 0.0;
	if (keycode == KEY_W)
	{
		movedir.x = P->dir.x;
		movedir.y = P->dir.y;
	}
	else if (keycode == KEY_S)
	{
		movedir.x = -(P->dir.x);
		movedir.y = -(P->dir.y);
	}
	else if (keycode == KEY_A)
	{
		movedir.x = (cos(-PI / 2) * P->dir.x - sin(-PI / 2) * P->dir.y);
		movedir.y = (sin(-PI / 2) * P->dir.x + cos(-PI / 2) * P->dir.y);
	}
	else if (keycode == KEY_D)
	{
		movedir.x = (cos(PI / 2) * P->dir.x - sin(PI / 2) * P->dir.y);
		movedir.y = (sin(PI / 2) * P->dir.x + cos(PI / 2) * P->dir.y);
	}
	return (move_(P, movedir));
}

int	quit(int keycode, PARAM *P)
{
	if (keycode != KEY_ESC)
		return (1);
	mlx_destroy_window(P->mlx, P->win);
	exit(0);
	return (0);
}

int	keymap(int keycode, PARAM *P)
{
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		return (rotate(keycode, P));
	else if (keycode == KEY_W || keycode == KEY_A || \
			keycode == KEY_S || keycode == KEY_D)
		return (move(keycode, P));
	else if (keycode == KEY_ESC)
		return (quit(keycode, P));
	else
		return (0);
}
