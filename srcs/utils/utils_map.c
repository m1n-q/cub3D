/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:03 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 16:15:46 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	set_dir(t_param *p, int c)
{
	if (c == 'N')
	{
		p->dir.x = 0.0;
		p->dir.y = -1.0;
	}
	else if (c == 'S')
	{
		p->dir.x = 0.0;
		p->dir.y = 1.0;
	}
	else if (c == 'W')
	{
		p->dir.x = -1.0;
		p->dir.y = 0.0;
	}
	else if (c == 'E')
	{
		p->dir.x = 1.0;
		p->dir.y = 0.0;
	}
	return (1);
}

int	set_pos(t_param *p, int x, int y)
{
	int	blockscale;

	blockscale = (SCREENWIDTH / 5);
	if (blockscale < 1)
		blockscale = 1;
	p->pos.x = (x + 0.5) * blockscale;
	p->pos.y = (y + 0.5) * blockscale;
	p->worldmap[y][x] = 0;
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

void	print_worldmap(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->cfg->mapheight)
	{
		j = 0;
		while (j < p->cfg->mapwidth)
		{
			if (p->worldmap[i][j] == 0 || p->worldmap[i][j] == 1)
				printf("%d", p->worldmap[i][j]);
			else
				printf("%c", p->worldmap[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
