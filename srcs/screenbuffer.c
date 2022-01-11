/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenbuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:16:50 by mishin            #+#    #+#             */
/*   Updated: 2022/01/11 11:16:58 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_buffer(PARAM *P)
{
	P->buf3D = (int **)malloc(sizeof(int *) * screenHeight);
	P->buf2D = (int **)malloc(sizeof(int *) * screenHeight);

	for (int i = 0; i < screenHeight; i++)
	{
		P->buf3D[i] = (int *)malloc(sizeof(int) * screenWidth);
		P->buf2D[i] = (int *)malloc(sizeof(int) * screenWidth);
	}

	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			P->buf3D[i][j] = 0;
			P->buf2D[i][j] = 0;
		}
	}

	return (0);
}

void	buffer_to_img(PARAM *P, int **buffer, IMG img, int w, int h)
{
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			img.addr[(y * img.linesize / sizeof(int) + x)] = buffer[y][x];
}

void	clear_buffer(PARAM *P, int **buffer)
{
	for (int y = 0; y < screenHeight; y++)
		for (int x = 0; x < screenWidth; x++)
			buffer[y][x] = 0;
}

void	clear_img(PARAM *P, IMG img)
{
	for (int y = 0; y < screenHeight; y++)
		for (int x = 0; x < screenWidth; x++)
			img.addr[(y * img.linesize / sizeof(int) + x)] = 0;
}
