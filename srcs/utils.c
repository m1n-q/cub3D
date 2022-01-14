/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:50 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 22:37:23 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	print_worldMap(PARAM *P)
{
	int i = 0;
	int j = 0;
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

void	err_exit(char *msg, PARAM *P)
{
	int	i;

	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);

	i = 0;
	if (P)
	{
		while (i < 4)
			free(P->tex_path[i++]);

		if (P->map)
			lst_clear(&P->map);

		if (P->worldMap)
		{
			i = 0;
			while (i < P->cfg->mapHeight)
				free(P->worldMap[i++]);
			free(P->worldMap);
		}
	}

	system("leaks cub3D &> res; cat res | grep leaked > res1; cat res1; rm res res1");
	exit(1);
}
