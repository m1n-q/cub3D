#include "cub3D.h"

void	check_x_axis(PARAM *P, int **M, int y)
{
	int	start;
	int	end;

	start = 0;
	while (check_val(M[y][start]) == 3)
		start++;
	end = P->cfg->mapWidth - 1;
	while (check_val(M[y][end]) == 3)
		end--;
	while (++start <= end)
	{
		if (M[y][start] == ' ')
		{
			if (M[y][start - 1] != 1)
				wall_leaks_exit(y, start - 1, P);
			while (M[y][start + 1] == ' ')
				start++;
			if (M[y][start + 1] != 1)
				wall_leaks_exit(y, start + 1, P);
		}
	}
}

static void	check_y_axis(PARAM *P, int **M, int x)
{
	int	start;
	int	end;

	start = 0;
	while (check_val(M[start][x]) == 3)
		start++;
	end = P->cfg->mapHeight - 1;
	while (check_val(M[end][x]) == 3)
		end--;
	while (++start <= end)
	{
		if (M[start][x] == ' ')
		{
			if (M[start - 1][x] != 1)
				wall_leaks_exit(start - 1, x, P);
			while (M[start + 1][x] == ' ')
				start++;
			if (M[start + 1][x] != 1)
				wall_leaks_exit(start + 1, x, P);
		}
	}
}

void	check_wall(PARAM *P)
{
	int	x;
	int	y;

	y = -1;
	while (++y < P->cfg->mapHeight)
		check_x_axis(P, P->worldMap, y);
	x = 0;
	while (++x < P->cfg->mapWidth)
		check_y_axis(P, P->worldMap, x);
}