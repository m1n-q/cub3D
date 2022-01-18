/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:15:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 17:56:24 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: t_img		=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)
void	make_minimap_image(t_param *p)
{
	p->grid.img = mlx_new_image(p->mlx, p->cfg->mapwidth * p->cfg->minimapscale, p->cfg->mapheight * p->cfg->minimapscale);
	p->grid.addr = (int *)mlx_get_data_addr(p->grid.img, &p->grid.bpp, &p->grid.linesize, &p->grid.endian);
	p->block.img = mlx_new_image(p->mlx, p->cfg->mapwidth * p->cfg->minimapscale, p->cfg->mapheight * p->cfg->minimapscale);
	p->block.addr = (int *)mlx_get_data_addr(p->block.img, &p->block.bpp, &p->block.linesize, &p->block.endian);
	p->hblock.img = mlx_new_image(p->mlx, p->cfg->mapwidth * p->cfg->minimapscale, p->cfg->mapheight * p->cfg->minimapscale);
	p->hblock.addr = (int *)mlx_get_data_addr(p->hblock.img, &p->hblock.bpp, &p->hblock.linesize, &p->hblock.endian);
	for (int x = 0; x < p->cfg->mapwidth * p->cfg->minimapscale; x++)
	{
		for (int y = 0; y < p->cfg->mapheight * p->cfg->minimapscale; y++)
		{
			p->grid.addr[y * p->block.linesize / sizeof(int) + x]	= 0x000000 ;
			p->block.addr[y * p->block.linesize / sizeof(int) + x]	= 0x5a7dbd ;
			p->hblock.addr[y * p->hblock.linesize / sizeof(int) + x] = 0x00fdff;

			if (x == 0 || y == 0 || x == p->cfg->mapwidth * p->cfg->minimapscale - 1 || y == p->cfg->mapheight * p->cfg->minimapscale -1)
				p->grid.addr[y * p->block.linesize / sizeof(int) + x] = 0x555555;
		}
	}
}

void	init_mlx_image(t_param *p)
{
	p->img3D.img = mlx_new_image(p->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!p->img3D.img)
		exit(1);
	p->img3D.addr = (int *)mlx_get_data_addr(p->img3D.img, &p->img3D.bpp, \
										&p->img3D.linesize, &p->img3D.endian);
	p->img2D.img = mlx_new_image(p->mlx, p->cfg->mapwidth * p->cfg->minimapscale, \
										p->cfg->mapheight * p->cfg->minimapscale);
	if (!p->img2D.img)
		exit(1);
	p->img2D.addr = (int *)mlx_get_data_addr(p->img2D.img, &p->img2D.bpp, \
											&p->img2D.linesize, &p->img2D.endian);
}

void	load_image(t_param *p, t_img *I, char *filename)
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
		err_exit(formatstr("not supported extension: {}", ext, 2), p);
	I->img = f(p->mlx, filename, &I->width, &I->height);
	if (!I->img)
		err_exit(formatstr("{}: load failed", filename, 0), p);
	I->addr = (int *)mlx_get_data_addr(I->img, &I->bpp, \
									&I->linesize, &I->endian);
	if (I->width != I->height || I->width != TEXWIDTH)
		err_exit(formatstr("{}: 256x256 image required.", filename, 0), p);
	printf("%s loaded\n", filename);
}

void	load_images(t_param *p)
{
	load_image(p, &p->wall_n, p->tex_path[N]);
	load_image(p, &p->wall_s, p->tex_path[S]);
	load_image(p, &p->wall_w, p->tex_path[W]);
	load_image(p, &p->wall_e, p->tex_path[E]);
}
