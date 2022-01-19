/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_worldMap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:47 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 13:45:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_left_right_wall(t_param *p, int y)
{
	int	x;

	x = 0;
	while (check_val(p->worldmap[y][x]) == 3 && x < p->cfg->mapwidth - 1)
		x++;
	if (p->worldmap[y][x] != 1)
		err_exit("wall leak", p);
	x = p->cfg->mapwidth - 1;
	while (check_val(p->worldmap[y][x]) == 3)
		x--;
	if (p->worldmap[y][x] != 1)
		err_exit("wall leak", p);
}

void	check_top_bottom_wall(t_param *p)
{
	int	x;
	int	y;

	x = -1;
	while (++x < p->cfg->mapwidth)
	{
		y = 0;
		while (check_val(p->worldmap[y][x]) == 3 && y < p->cfg->mapheight - 1)
			y++;
		if (p->worldmap[y][x] != 1)
			err_exit("wall leak", p);
		y = p->cfg->mapheight - 1;
		while (check_val(p->worldmap[y][x]) == 3)
			y--;
		if (p->worldmap[y][x] != 1)
			err_exit("wall leak", p);
	}
}

void	check_worldmap(t_param *p, t_config *cfg)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (y < cfg->mapheight)
	{
		x = 0;
		while (x < cfg->mapwidth)
		{
			if (!check_val(p->worldmap[y][x]))
				err_exit("invalid val in map", p);
			if (check_val(p->worldmap[y][x]) == 1)
				player += (set_dir(p, p->worldmap[y][x]) && set_pos(p, x, y));
			x++;
		}
		check_left_right_wall(p, y);
		check_hole(p, y);
		y++;
	}
	check_top_bottom_wall(p);
	check_wall(p);
	if (player != 1)
		err_exit("wrong player numer", p);
}

// 10 가장 왼쪽 벽을 체크합니다 in a line
// 15 가장 오른쪽 벽이 체크됩니다 in a line
// 30 (해당 열에서) 가장 윗쪽 벽을 체크합니다
// 35 (해당 열에서) 가장 아래쪽 벽을 체크합니다
