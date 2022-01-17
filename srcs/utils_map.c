#include "cub3D.h"

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

void	print_worldMap(PARAM *P)
{
	int	i;
	int	j;

	i = 0;
	while (i < P->cfg->mapHeight)
	{
		j = 0;
		while (j < P->cfg->mapWidth)
		{
			if (P->worldMap[i][j] == 0 || P->worldMap[i][j] == 1)
				printf("%d", P->worldMap[i][j]);
			else
				printf("%c", P->worldMap[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	wall_leaks_exit(int y, int x, PARAM *P)
{
	printf(P_RED "=> y:[%d], x:[%d] <=\n" P_RESET, y, x);
	err_exit(" ERROR: wall leak", P);
}