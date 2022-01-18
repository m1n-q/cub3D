#include "cub3D.h"

int	set_dir(t_param *P, int c)
{
	if (c == 'N')
	{
		P->dir.x = 0.0;
		P->dir.y = -1.0;
	}
	else if (c == 'S')
	{
		P->dir.x = 0.0;
		P->dir.y = 1.0;
	}
	else if (c == 'W')
	{
		P->dir.x = -1.0;
		P->dir.y = 0.0;
	}
	else if (c == 'E')
	{
		P->dir.x = 1.0;
		P->dir.y = 0.0;
	}
	return (1);
}

int	set_pos(t_param *P, int x, int y)
{
	int	blockscale;

	blockscale = (SCREENWIDTH / P->cfg->mapwidth);
	P->pos.x = (x + 0.5) * blockscale;
	P->pos.y = (y + 0.5) * blockscale;
	P->worldmap[y][x] = 0;
	return (1);
}

int	check_val(int c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	if (c == 1 || c == 0)
		return (2);
	if (c == ' ' || c == '\t')
		return (3);
	else
		return (0);
}

void	print_worldmap(t_param *P)
{
	int	i;
	int	j;

	i = 0;
	while (i < P->cfg->mapheight)
	{
		j = 0;
		while (j < P->cfg->mapwidth)
		{
			if (P->worldmap[i][j] == 0 || P->worldmap[i][j] == 1)
				printf("%d", P->worldmap[i][j]);
			else
				printf("%c", P->worldmap[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	wall_leaks_exit(int y, int x, t_param *P)
{
	printf(P_RED "=> y:[%d], x:[%d] <=\n" P_RESET, y, x);
	err_exit(" ERROR: wall leak", P);
}

