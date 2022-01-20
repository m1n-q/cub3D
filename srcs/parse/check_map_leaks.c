/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_leaks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:29 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:16:29 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_map_leaks(t_param *p, int **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < p->cfg->mapheight)
	{
		x = 0;
		while (x < p->cfg->mapwidth)
		{
			if (map[y][x] == 0)
			{
				if (y == 0 || y == p->cfg->mapheight - 1
					|| x == 0 || x == p->cfg->mapwidth - 1)
					err_exit("MAP LEAKS", p);
				else if (check_val(map[y][x - 1]) == SPACE
						|| check_val(map[y][x + 1]) == SPACE
						|| check_val(map[y - 1][x]) == SPACE
						|| check_val(map[y + 1][x]) == SPACE)
					err_exit("MAP LEAKS", p);
			}
			x++;
		}
		y++;
	}
}
