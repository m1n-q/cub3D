/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:13:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/11 11:45:34 by mishin           ###   ########.fr       */
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


//NOTE: dir.x == 0 || dir.y == 0 일 때와 움직이는 양이 다른가...?
//NOTE: 벽따라 미끄러지는 느낌으로?
//TODO: 충돌감지 원
int	move(int keycode, PARAM *P)
{
	int		amount = 5;
	VECTOR	oldpos = P->pos;

	if (keycode == KEY_W)
	{
		P->pos.x += P->dir.x * amount;
		P->pos.y += P->dir.y * amount;
	}
	else if (keycode == KEY_S)
	{
 		P->pos.x -= P->dir.x * amount;
		P->pos.y -= P->dir.y * amount;
	}
	else if (keycode == KEY_A) //dir 의 -90도 회전방향
	{
		P->pos.x += (cos(-PI / 2) * P->dir.x - sin(-PI / 2) * P->dir.y) * amount;
		P->pos.y += (sin(-PI / 2) * P->dir.x + cos(-PI / 2) * P->dir.y) * amount;
	}
	else if (keycode == KEY_D) //dir 의 +90도 회전방향
	{
		P->pos.x += (cos(PI / 2) * P->dir.x - sin(PI / 2) * P->dir.y) * amount;
		P->pos.y += (sin(PI / 2) * P->dir.x + cos(PI / 2) * P->dir.y) * amount;
	}

	if (worldMap[(int)P->pos.y / BLOCK_SIZE][(int)P->pos.x / BLOCK_SIZE])
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