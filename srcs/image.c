/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:15:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/15 19:20:58 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: IMG		=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)

int make_block_image(PARAM *P)
{
	P->grid.img = mlx_new_image(P->mlx, P->cfg->mapWidth * P->cfg->minimapScale, P->cfg->mapHeight * P->cfg->minimapScale);
	P->grid.addr = (int *)mlx_get_data_addr(P->grid.img, &P->grid.bpp, &P->grid.linesize, &P->grid.endian);
	P->block.img = mlx_new_image(P->mlx, P->cfg->mapWidth * P->cfg->minimapScale, P->cfg->mapHeight * P->cfg->minimapScale);
	P->block.addr = (int *)mlx_get_data_addr(P->block.img, &P->block.bpp, &P->block.linesize, &P->block.endian);
	P->hblock.img = mlx_new_image(P->mlx, P->cfg->mapWidth * P->cfg->minimapScale, P->cfg->mapHeight * P->cfg->minimapScale);
	P->hblock.addr = (int *)mlx_get_data_addr(P->hblock.img, &P->hblock.bpp, &P->hblock.linesize, &P->hblock.endian);
	for (int x = 0; x < P->cfg->mapWidth * P->cfg->minimapScale; x++)
	{
		for (int y = 0; y < P->cfg->mapHeight * P->cfg->minimapScale; y++)
		{
			P->grid.addr[y * P->block.linesize / sizeof(int) + x]	= 0x000000 ;
			P->block.addr[y * P->block.linesize / sizeof(int) + x]	= 0x5a7dbd ;
			P->hblock.addr[y * P->hblock.linesize / sizeof(int) + x] = 0x00fdff;

			if (x == 0 || y == 0 || x == P->cfg->mapWidth * P->cfg->minimapScale - 1 || y == P->cfg->mapHeight * P->cfg->minimapScale -1)
				P->grid.addr[y * P->block.linesize / sizeof(int) + x] = RGB_Grey;
		}
	}
	return (0);
}

int	init_mlx_image(PARAM *P)
{
	P->img3D.img = mlx_new_image(P->mlx, P->cfg->screenWidth, P->cfg->screenHeight);
	P->img3D.addr = (int *)mlx_get_data_addr(P->img3D.img, &P->img3D.bpp, &P->img3D.linesize, &P->img3D.endian);
	P->img2D.img = mlx_new_image(P->mlx, P->cfg->mapWidth * P->cfg->minimapScale, P->cfg->mapHeight * P->cfg->minimapScale);
	P->img2D.addr = (int *)mlx_get_data_addr(P->img2D.img, &P->img2D.bpp, &P->img2D.linesize, &P->img2D.endian);
	return (0);
}


int load_image(PARAM *P, IMG *I, char *filename)
{
	char		*ext;
	loadfunc	f;

	printf("loading %s", filename);
	f = NULL;
	ext = ft_substr(filename, ft_strlen(filename) - 3, 3);

	if (ft_strncmp(ext, "xpm", 3) == 0)
		f = mlx_xpm_file_to_image;
	else if (ft_strncmp(ext, "png", 3) == 0)
		f = mlx_png_file_to_image;
	else
		err_exit("Not supported ext : ===", P);	//TODO

	I->img = f(P->mlx, filename, &I->width, &I->height);
	I->addr = (int *)mlx_get_data_addr(I->img, &I->bpp, &I->linesize, &I->endian);
	if (I->img && I->addr)
		printf("\r%s loaded.\n", filename);
	return (0);
}

int load_images(PARAM *P)
{
	int	any;

	any = 0;	//for err
	// wall texture
	load_image(P, &P->wall1, "rscs/mybrick_256.png");
	load_image(P, &P->wall2, "rscs/wood1_256.png");
	load_image(P, &P->wall3, "rscs/wood2_256.png");
	load_image(P, &P->wall4, "rscs/wood3_256.png");
	load_image(P, &P->wall5, "rscs/wall2_256.png");

	// NSWE
	load_image(P, &P->wall_N, P->tex_path[N]);
	load_image(P, &P->wall_S, P->tex_path[S]);
	load_image(P, &P->wall_W, P->tex_path[W]);
	load_image(P, &P->wall_E, P->tex_path[E]);

	return (0);
}
