#include "cub3D.h"

void	check_left_right_wall(PARAM *P, int y)
{
	int	x;

	x = 0;
	while (check_val(P->worldMap[y][x]) == 3 && x < P->cfg->mapWidth - 1)
		x++;
	if (P->worldMap[y][x] != 1)
		wall_leaks_exit(y, x, P);
	x = P->cfg->mapWidth - 1;
	while (check_val(P->worldMap[y][x]) == 3)
		x--;
	if (P->worldMap[y][x] != 1)
		wall_leaks_exit(y, x, P);
}

void	check_top_bottom_wall(PARAM *P)
{
	int	x;
	int	y;

	x = -1;
	while (++x < P->cfg->mapWidth)
	{
		y = 0;
		while (check_val(P->worldMap[y][x]) == 3 && y < P->cfg->mapHeight - 1)
			y++;
		if (P->worldMap[y][x] != 1)
			wall_leaks_exit(y, x, P);
		y = P->cfg->mapHeight - 1;
		while (check_val(P->worldMap[y][x]) == 3)
			y--;
		if (P->worldMap[y][x] != 1)
			wall_leaks_exit(y, x, P);
	}
}

void	check_worldMap(PARAM *P, CONFIG *C)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (y < C->mapHeight)
	{
		x = 0;
		while (x < C->mapWidth)
		{
			if (!check_val(P->worldMap[y][x]))
				err_exit("ERROR: invalid val in map", P);
			if (check_val(P->worldMap[y][x]) == 1)
				player = (set_dir(P, P->worldMap[y][x]) && set_pos(P, x, y));
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
