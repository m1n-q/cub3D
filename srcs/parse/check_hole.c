/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hole.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:26 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:16:26 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_y_axis(t_param *p, int y, int x)
{
	int	old_y;
	int	block;

	old_y = y;
	block = 0;
	while (--y >= 0)
	{
		if (p->worldmap[y][x] != ' ')
		{
			block += 1;
			break ;
		}
	}
	y = old_y;
	while (++y < p->cfg->mapheight)
	{
		if (p->worldmap[y][x] != ' ')
		{
			block += 1;
			break ;
		}
	}
	if (block == 2)
		err_exit("found a hole in map", p);
}

void	check_hole(t_param *p, int y)
{
	int		start;
	int		end;
	int		x;

	start = 0;
	while (p->worldmap[y][start] == ' ')
		start++;
	end = p->cfg->mapwidth - 1;
	while (p->worldmap[y][end] == ' ')
		end--;
	x = start;
	while (x < end)
	{
		if (p->worldmap[y][x] == ' ')
			check_y_axis(p, y, x);
		x++;
	}
}
