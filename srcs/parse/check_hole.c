#include "cub3D.h"

static void	check_y_axis(t_param *P, int y, int x)
{
	int	old_y;
	int	block;

	old_y = y;
	block = 0;
	while (--y >= 0)
	{
		if (P->worldMap[y][x] != ' ')
		{
			block += 1;
			break ;
		}
	}
	y = old_y;
	while (++y < P->cfg->mapHeight)
	{
		if (P->worldMap[y][x] != ' ')
		{
			block += 1;
			break ;
		}
	}
	if (block == 2)
		err_exit("ERROR: found a hole in map", P);
}

void	check_hole(t_param *P, int y)
{
	int		start;
	int		end;
	int		x;

	start = 0;
	while (P->worldMap[y][start] == ' ')
		start++;
	end = P->cfg->mapWidth - 1;
	while (P->worldMap[y][end] == ' ')
		end--;
	x = start;
	while (x < end)
	{
		if (P->worldMap[y][x] == ' ')
			check_y_axis(P, y, x);
		x++;
	}
}
