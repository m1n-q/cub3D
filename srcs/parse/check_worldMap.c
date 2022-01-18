#include "cub3D.h"

void	check_left_right_wall(t_param *P, int y)
{
	int	x;

	x = 0;
	while (check_val(P->worldmap[y][x]) == 3 && x < P->cfg->mapwidth - 1)
		x++;
	if (P->worldmap[y][x] != 1)
		wall_leaks_exit(y, x, P);
	x = P->cfg->mapwidth - 1;
	while (check_val(P->worldmap[y][x]) == 3)
		x--;
	if (P->worldmap[y][x] != 1)
		wall_leaks_exit(y, x, P);
}

void	check_top_bottom_wall(t_param *P)
{
	int	x;
	int	y;

	x = -1;
	while (++x < P->cfg->mapwidth)
	{
		y = 0;
		while (check_val(P->worldmap[y][x]) == 3 && y < P->cfg->mapheight - 1)
			y++;
		if (P->worldmap[y][x] != 1)
			wall_leaks_exit(y, x, P);
		y = P->cfg->mapheight - 1;
		while (check_val(P->worldmap[y][x]) == 3)
			y--;
		if (P->worldmap[y][x] != 1)
			wall_leaks_exit(y, x, P);
	}
}

void	check_worldmap(t_param *P, t_config *C)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (y < C->mapheight)
	{
		x = 0;
		while (x < C->mapwidth)
		{
			if (!check_val(P->worldmap[y][x]))
				err_exit("ERROR: invalid val in map", P);
			if (check_val(P->worldmap[y][x]) == 1)
				player = (set_dir(P, P->worldmap[y][x]) && set_pos(P, x, y));
			x++;
		}
		check_left_right_wall(P, y);
		check_hole(P, y);
		y++;
	}
	check_top_bottom_wall(P);
	check_wall(P);
	if (player != 1)
		err_exit("ERROR: wrong player numer", P);
}

// 10 가장 왼쪽 벽을 체크합니다 in a line
// 15 가장 오른쪽 벽이 체크됩니다 in a line
// 30 (해당 열에서) 가장 윗쪽 벽을 체크합니다
// 35 (해당 열에서) 가장 아래쪽 벽을 체크합니다
