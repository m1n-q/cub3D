#include "cub3D.h"

void	check_x_axis(t_param *P, int **M, int y)
{
	int	start;
	int	end;

	start = 0;
	while (check_val(M[y][start]) == 3)
		start++;
	end = P->cfg->mapwidth - 1;
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

static void	check_y_axis(t_param *P, int **M, int x)
{
	int	start;
	int	end;

	start = 0;
	while (check_val(M[start][x]) == 3)
		start++;
	end = P->cfg->mapheight - 1;
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

void	check_wall(t_param *P)
{
	int	x;
	int	y;

	y = -1;
	while (++y < P->cfg->mapheight)
		check_x_axis(P, P->worldmap, y);
	x = 0;
	while (++x < P->cfg->mapwidth)
		check_y_axis(P, P->worldmap, x);
}
