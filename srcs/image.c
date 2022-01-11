/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:15:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/11 11:24:07 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int load_image(PARAM *P)
{
	P->img3D.img = mlx_new_image(P->mlx, screenWidth, screenHeight);
	P->img3D.addr = (int *)mlx_get_data_addr(P->img3D.img, &P->img3D.bpp, &P->img3D.linesize, &P->img3D.endian);

	P->img2D.img = mlx_new_image(P->mlx, screenWidth, screenHeight);
	P->img2D.addr = (int *)mlx_get_data_addr(P->img2D.img, &P->img2D.bpp, &P->img2D.linesize, &P->img2D.endian);

	P->grid.img = mlx_png_file_to_image(P->mlx, "rscs/grid20.png", &P->grid.width, &P->grid.height);
	P->grid.addr = (int *)mlx_get_data_addr(P->grid.img, &P->grid.bpp, &P->grid.linesize, &P->grid.endian);

	P->block.img = mlx_xpm_file_to_image(P->mlx, "rscs/block_blue.xpm", &P->block.width, &P->block.height);
	P->block.addr = (int *)mlx_get_data_addr(P->block.img, &P->block.bpp, &P->block.linesize, &P->block.endian);

	P->hblock.img = mlx_png_file_to_image(P->mlx, "rscs/block_cyan.png", &P->hblock.width, &P->hblock.height);
	P->hblock.addr = (int *)mlx_get_data_addr(P->hblock.img, &P->hblock.bpp, &P->hblock.linesize, &P->hblock.endian);

	P->wall1.img = mlx_png_file_to_image(P->mlx, "rscs/mybrick_256.png", &P->wall1.width, &P->wall1.height);
	P->wall1.addr = (int *)mlx_get_data_addr(P->wall1.img, &P->wall1.bpp, &P->wall1.linesize, &P->wall1.endian);

	P->wall2.img = mlx_png_file_to_image(P->mlx, "rscs/wood1_256.png", &P->wall2.width, &P->wall2.height);
	P->wall2.addr = (int *)mlx_get_data_addr(P->wall2.img, &P->wall2.bpp, &P->wall2.linesize, &P->wall2.endian);

	P->wall3.img = mlx_png_file_to_image(P->mlx, "rscs/wood2_256.png", &P->wall3.width, &P->wall3.height);
	P->wall3.addr = (int *)mlx_get_data_addr(P->wall3.img, &P->wall3.bpp, &P->wall3.linesize, &P->wall3.endian);

	P->wall4.img = mlx_png_file_to_image(P->mlx, "rscs/wood3_256.png", &P->wall4.width, &P->wall4.height);
	P->wall4.addr = (int *)mlx_get_data_addr(P->wall4.img, &P->wall4.bpp, &P->wall4.linesize, &P->wall4.endian);

	return (0);
}
