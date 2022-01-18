/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenbuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:16:50 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 16:51:00 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: buffer	=> 직관적으로 생각할 수 있는 2차원 배열 형태
int	init_buffer(t_param *P)
{
	int	i;

	P->buf3D = (int **)calloc_(screenHeight, sizeof(int *));
	i = -1;
	while (++i < screenHeight)
		P->buf3D[i] = (int *)calloc_(screenWidth, sizeof(int));

	P->buf2D = (int **)calloc_(P->cfg->mapHeight * P->cfg->minimapScale, sizeof(int *));
	i = -1;
	while (++i < P->cfg->mapHeight * P->cfg->minimapScale)
		P->buf2D[i] = (int *)calloc_(P->cfg->mapWidth * P->cfg->minimapScale, sizeof(int));
	return (0);
}

void	destroy_buffer(t_param* P)
{
	int	i;

	i = -1;
	while (++i < screenHeight)
		free(P->buf3D[i]);
	i = -1;
	while (++i < P->cfg->mapHeight * P->cfg->minimapScale)
		free(P->buf2D[i]);
	free(P->buf3D);
	free(P->buf2D);
}

void	buffer_to_img(int **buffer, t_img img, int w, int h)
{
	int	x;
	int	y;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			img.addr[(y * img.linesize / sizeof(int) + x)] = buffer[y][x];
	}
}

void	clear_buffer(int **buffer, int w, int h)
{
	int	x;
	int	y;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			buffer[y][x] = 0;
	}
}

void	clear_img(t_img img, int w, int h)
{
	int	x;
	int	y;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			img.addr[(y * img.linesize / sizeof(int) + x)] = 0;
	}
}
