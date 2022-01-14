/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenbuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:16:50 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 16:37:09 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: buffer	=> 직관적으로 생각할 수 있는 2차원 배열 형태
int	init_buffer(PARAM *P)
{

	P->buf3D = (int **)ft_calloc(screenHeight, sizeof(int *));
	for (int i = 0; i < screenHeight; i++)
		P->buf3D[i] = (int *)ft_calloc(screenWidth, sizeof(int));

	P->buf2D = (int **)ft_calloc(mapHeight * minimapScale, sizeof(int *));
	for (int i = 0; i < mapHeight * minimapScale; i++)
		P->buf2D[i] = (int *)ft_calloc(mapWidth * minimapScale, sizeof(int));
	return (0);
}

void	destroy_buffer(PARAM* P)
{
	for (int i = 0; i < screenHeight; i++)
		free(P->buf3D[i]);
	for (int i = 0; i < mapHeight * minimapScale; i++)
		free(P->buf2D[i]);

	free(P->buf3D);
	free(P->buf2D);
}

void	buffer_to_img(int **buffer, IMG img, int w, int h)
{
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			img.addr[(y * img.linesize / sizeof(int) + x)] = buffer[y][x];
}

void	clear_buffer(int **buffer, int w, int h)
{
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			buffer[y][x] = 0;
}

void	clear_img(IMG img, int w, int h)
{
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			img.addr[(y * img.linesize / sizeof(int) + x)] = 0;
}

