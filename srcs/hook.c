#include "cub3D.h"

int move(int keycode, PARAM *P)
{
	double rot_angle = 0.2;
	double	old_dirx;
	if (keycode == KEY_RIGHT)
	{
		old_dirx = P->dir.x;
		P->dir.x = cos(rot_angle) * P->dir.x - sin(rot_angle) * P->dir.y;
		P->dir.y = sin(rot_angle) * old_dirx + cos(rot_angle) * P->dir.y;
	}
	if (keycode == KEY_LEFT)
	{
		old_dirx = P->dir.x;
		P->dir.x = cos(-rot_angle) * P->dir.x - sin(-rot_angle) * P->dir.y;
		P->dir.y = sin(-rot_angle) * old_dirx + cos(-rot_angle) * P->dir.y;
	}
	if (keycode == KEY_W)
	{
		if (worldMap[(int)(P->pos.y) / BLOCK_SIZE][(int)(P->pos.x + P->dir.x) / BLOCK_SIZE] == false)
      		P->pos.x += P->dir.x * 5;
		if (worldMap[(int)(P->pos.y + P->dir.y) / BLOCK_SIZE][(int)(P->pos.x) / BLOCK_SIZE] == false)
			P->pos.y += P->dir.y * 5;
	}
	if (keycode == KEY_A)
	{
		;
	}
	if (keycode == KEY_S)
	{
		;
	}
	if (keycode == KEY_D)
	{
		;
	}
	render(P);
	return (0);
}

int movecur(int x, int y, PARAM *P)
{

	if (x < screenWidth && y < screenHeight)
	{
		P->pos.x = x;
		P->pos.y = y;
		// render(P);
	}
	return (0);
}
