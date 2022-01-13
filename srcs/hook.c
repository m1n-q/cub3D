/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:13:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/13 17:14:38 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rotate(int keycode, PARAM *P)
{
	double	rot_angle = 0.2;
	double	old_dirx;

	if (keycode == KEY_RIGHT)
	{
		old_dirx = P->dir.x;
		P->dir.x = cos(rot_angle) * P->dir.x - sin(rot_angle) * P->dir.y;
		P->dir.y = sin(rot_angle) * old_dirx + cos(rot_angle) * P->dir.y;
	}
	else if (keycode == KEY_LEFT)
	{
		old_dirx = P->dir.x;
		P->dir.x = cos(-rot_angle) * P->dir.x - sin(-rot_angle) * P->dir.y;
		P->dir.y = sin(-rot_angle) * old_dirx + cos(-rot_angle) * P->dir.y;
	}
	return (0);
}



//TODO: 충돌감지 원
int	checkCollision(PARAM *P, double radius)
{
	for (double r = 0.0; r <= PI * 2 ; r += 0.03)
	{
		double dX = 0.0, dY = 0.0;
		VECTOR newdir;

		newdir.x = cos(r) * P->dir.x - sin(r) * P->dir.y;
		newdir.y = sin(r) * P->dir.x + cos(r) * P->dir.y;
		for (int linelength = 0; linelength < radius; linelength++)
		{
			dX += newdir.x;
			dY += newdir.y;
			if (worldMap[(int)((int)(P->pos.y + dY) / BLOCK_SIZE)][(int)((int)(P->pos.x + dX) / BLOCK_SIZE)])
				return (1);
		}
	}
	return (0);
}

//NOTE: dir.x == 0 || dir.y == 0 일 때와 움직이는 양이 다른가...?
int	move(int keycode, PARAM *P)
{
	int		amount = 5;
	VECTOR	oldpos = P->pos;
	VECTOR	movedir;
	if (keycode == KEY_W)
	{
		movedir.x = P->dir.x;
		movedir.y = P->dir.y;
	}
	else if (keycode == KEY_S)
	{
 		movedir.x = -P->dir.x;
		movedir.y = -P->dir.y;
	}
	else if (keycode == KEY_A) //dir 의 -90도 회전방향
	{
		movedir.x = (cos(-PI / 2) * P->dir.x - sin(-PI / 2) * P->dir.y);
		movedir.y = (sin(-PI / 2) * P->dir.x + cos(-PI / 2) * P->dir.y);
	}
	else if (keycode == KEY_D) //dir 의 +90도 회전방향
	{
		movedir.x = (cos(PI / 2) * P->dir.x - sin(PI / 2) * P->dir.y);
		movedir.y = (sin(PI / 2) * P->dir.x + cos(PI / 2) * P->dir.y);
	}


	P->pos.x += movedir.x * amount;
	if (checkCollision(P, collisionRange))
		P->pos = oldpos;

	oldpos = P->pos;
	P->pos.y += movedir.y * amount;
	if (checkCollision(P, collisionRange))
		P->pos = oldpos;

	return (0);
}

int	quit(int keycode, PARAM *P)
{
	mlx_destroy_window(P->mlx, P->win);
	exit(0);

	return (0);	//NOREACH
}

int	keymap(int keycode, PARAM *P)
{
	if		(keycode == KEY_RIGHT || keycode == KEY_LEFT)	return (rotate(keycode, P));

	else if	(keycode == KEY_W || keycode == KEY_A || \
			keycode == KEY_S || keycode == KEY_D)			return (move(keycode, P));

	else if	(keycode == KEY_ESC)							return (quit(keycode, P));

	else													return (0);
}
