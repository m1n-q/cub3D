/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:29 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:16:29 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_x_axis(t_param *p, int **M, int y)
{
	int	start;
	int	end;

	start = 0;
	while (check_val(M[y][start]) == 3)
		start++;
	end = p->cfg->mapwidth - 1;
	while (check_val(M[y][end]) == 3)
		end--;
	while (++start <= end)
	{
		if (M[y][start] == ' ')
		{
			if (M[y][start - 1] != 1)
				err_exit("wall leak", p);
			while (M[y][start + 1] == ' ')
				start++;
			if (M[y][start + 1] != 1)
				err_exit("wall leak", p);
		}
	}
}

static void	check_y_axis(t_param *p, int **M, int x)
{
	int	start;
	int	end;

	start = 0;
	while (check_val(M[start][x]) == 3)
		start++;
	end = p->cfg->mapheight - 1;
	while (check_val(M[end][x]) == 3)
		end--;
	while (++start <= end)
	{
		if (M[start][x] == ' ')
		{
			if (M[start - 1][x] != 1)
				err_exit("wall leak", p);
			while (M[start + 1][x] == ' ')
				start++;
			if (M[start + 1][x] != 1)
				err_exit("wall leak", p);
		}
	}
}

void	check_wall(t_param *p)
{
	int	x;
	int	y;

	y = -1;
	while (++y < p->cfg->mapheight)
		check_x_axis(p, p->worldmap, y);
	x = -1;
	while (++x < p->cfg->mapwidth)
		check_y_axis(p, p->worldmap, x);
}
