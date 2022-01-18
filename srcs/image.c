/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:15:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 17:06:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: t_img		=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)
void	make_minimap_image(t_param *P)
{
	P->grid.img = mlx_new_image(P->mlx, P->cfg->mapwidth * P->cfg->minimapscale, P->cfg->mapheight * P->cfg->minimapscale);
	P->grid.addr = (int *)mlx_get_data_addr(P->grid.img, &P->grid.bpp, &P->grid.linesize, &P->grid.endian);
	P->block.img = mlx_new_image(P->mlx, P->cfg->mapwidth * P->cfg->minimapscale, P->cfg->mapheight * P->cfg->minimapscale);
	P->block.addr = (int *)mlx_get_data_addr(P->block.img, &P->block.bpp, &P->block.linesize, &P->block.endian);
	P->hblock.img = mlx_new_image(P->mlx, P->cfg->mapwidth * P->cfg->minimapscale, P->cfg->mapheight * P->cfg->minimapscale);
	P->hblock.addr = (int *)mlx_get_data_addr(P->hblock.img, &P->hblock.bpp, &P->hblock.linesize, &P->hblock.endian);
	for (int x = 0; x < P->cfg->mapwidth * P->cfg->minimapscale; x++)
	{
		for (int y = 0; y < P->cfg->mapheight * P->cfg->minimapscale; y++)
		{
			P->grid.addr[y * P->block.linesize / sizeof(int) + x]	= 0x000000 ;
			P->block.addr[y * P->block.linesize / sizeof(int) + x]	= 0x5a7dbd ;
			P->hblock.addr[y * P->hblock.linesize / sizeof(int) + x] = 0x00fdff;

			if (x == 0 || y == 0 || x == P->cfg->mapwidth * P->cfg->minimapscale - 1 || y == P->cfg->mapheight * P->cfg->minimapscale -1)
				P->grid.addr[y * P->block.linesize / sizeof(int) + x] = RGB_Grey;
		}
	}
}

void	init_mlx_image(t_param *P)
{
	P->img3D.img = mlx_new_image(P->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!P->img3D.img)
		exit(1);
	P->img3D.addr = (int *)mlx_get_data_addr(P->img3D.img, &P->img3D.bpp, \
										&P->img3D.linesize, &P->img3D.endian);
	P->img2D.img = mlx_new_image(P->mlx, P->cfg->mapwidth * P->cfg->minimapscale, \
										P->cfg->mapheight * P->cfg->minimapscale);
	if (!P->img2D.img)
		exit(1);
	P->img2D.addr = (int *)mlx_get_data_addr(P->img2D.img, &P->img2D.bpp, \
											&P->img2D.linesize, &P->img2D.endian);
}

void	load_image(t_param *P, t_img *I, char *filename)
{
	char		*ext;
	t_loadfunc	f;

	printf("loading %s...\n", filename);
	f = NULL;
	ext = substr_(filename, ft_strlen(filename) - 3, 3);
	if (ft_strncmp(ext, "xpm", 3) == 0)
		f = mlx_xpm_file_to_image;
	else if (ft_strncmp(ext, "png", 3) == 0)
		f = mlx_png_file_to_image;
	else
		err_exit(formatstr("not supported extension: {}", ext, 2), P);
	I->img = f(P->mlx, filename, &I->width, &I->height);
	if (!I->img)
		err_exit(formatstr("{}: load failed", filename, 0), P);
	I->addr = (int *)mlx_get_data_addr(I->img, &I->bpp, \
									&I->linesize, &I->endian);
	if (I->width != I->height || I->width != TEXWIDTH)
		err_exit(formatstr("{}: 256x256 image required.", filename, 0), P);
	printf("%s loaded\n", filename);
}

void	load_images(t_param *P)
{
	load_image(P, &P->wall_n, P->tex_path[N]);
	load_image(P, &P->wall_s, P->tex_path[S]);
	load_image(P, &P->wall_w, P->tex_path[W]);
	load_image(P, &P->wall_e, P->tex_path[E]);
}
