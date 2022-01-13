/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:15:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/13 21:38:59 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: IMG		=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)

int make_block_image(PARAM *P)
{
	P->grid.img = mlx_new_image(P->mlx, BLOCK_SIZE, BLOCK_SIZE);
	P->grid.addr = (int *)mlx_get_data_addr(P->grid.img, &P->grid.bpp, &P->grid.linesize, &P->grid.endian);
	P->block.img = mlx_new_image(P->mlx, BLOCK_SIZE, BLOCK_SIZE);
	P->block.addr = (int *)mlx_get_data_addr(P->block.img, &P->block.bpp, &P->block.linesize, &P->block.endian);
	P->hblock.img = mlx_new_image(P->mlx, BLOCK_SIZE, BLOCK_SIZE);
	P->hblock.addr = (int *)mlx_get_data_addr(P->hblock.img, &P->hblock.bpp, &P->hblock.linesize, &P->hblock.endian);
	for (int x = 0; x < BLOCK_SIZE; x++)
	{
		for (int y = 0; y < BLOCK_SIZE; y++)
		{
			P->grid.addr[y * P->block.linesize / sizeof(int) + x]	= 0x000000 ;
			P->block.addr[y * P->block.linesize / sizeof(int) + x]	= 0x5a7dbd ;
			P->hblock.addr[y * P->hblock.linesize / sizeof(int) + x] = 0x00fdff;

			if (x == 0 || y == 0 || x == BLOCK_SIZE -1 || y == BLOCK_SIZE -1)
				P->grid.addr[y * P->block.linesize / sizeof(int) + x] = RGB_Grey;
		}
	}
	return (0);
}

int	init_mlx_image(PARAM *P)
{
	P->img3D.img = mlx_new_image(P->mlx, screenWidth, screenHeight);
	P->img3D.addr = (int *)mlx_get_data_addr(P->img3D.img, &P->img3D.bpp, &P->img3D.linesize, &P->img3D.endian);
	P->img2D.img = mlx_new_image(P->mlx, screenWidth, screenHeight);
	P->img2D.addr = (int *)mlx_get_data_addr(P->img2D.img, &P->img2D.bpp, &P->img2D.linesize, &P->img2D.endian);
	return (0);
}

int load_image(PARAM *P)
{
	P->wall1.img = mlx_png_file_to_image(P->mlx, "rscs/mybrick_256.png", \
										&P->wall1.width, &P->wall1.height);
	P->wall1.addr = (int *)mlx_get_data_addr(P->wall1.img, &P->wall1.bpp, \
											&P->wall1.linesize, &P->wall1.endian);
	P->wall2.img = mlx_png_file_to_image(P->mlx, "rscs/wood1_256.png", \
										&P->wall2.width, &P->wall2.height);
	P->wall2.addr = (int *)mlx_get_data_addr(P->wall2.img, &P->wall2.bpp, \
											&P->wall2.linesize, &P->wall2.endian);
	P->wall3.img = mlx_png_file_to_image(P->mlx, "rscs/wood2_256.png", \
										&P->wall3.width, &P->wall3.height);
	P->wall3.addr = (int *)mlx_get_data_addr(P->wall3.img, &P->wall3.bpp, \
											&P->wall3.linesize, &P->wall3.endian);
	P->wall4.img = mlx_png_file_to_image(P->mlx, "rscs/wood3_256.png", \
										&P->wall4.width, &P->wall4.height);
	P->wall4.addr = (int *)mlx_get_data_addr(P->wall4.img, &P->wall4.bpp, \
										&P->wall4.linesize, &P->wall4.endian);
	P->wall5.img = mlx_png_file_to_image(P->mlx, "rscs/wall2_256.png", \
										&P->wall5.width, &P->wall5.height);
	P->wall5.addr = (int *)mlx_get_data_addr(P->wall5.img, &P->wall5.bpp, \
										&P->wall5.linesize, &P->wall5.endian);
	return (0);
}
