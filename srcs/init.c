/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:46 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 22:28:32 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_mlx_img(t_param *p)
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

//NOTE: buffer	=> 직관적으로 생각할 수 있는 2차원 배열 형태
static int	init_buffer(t_param *p)
{
	int	i;

	p->buf3D = (int **)calloc_(SCREENHEIGHT, sizeof(int *));
	i = -1;
	while (++i < SCREENHEIGHT)
		p->buf3D[i] = (int *)calloc_(SCREENWIDTH, sizeof(int));
	p->buf2D = (int **)calloc_(p->cfg->mapheight * p->cfg->minimapscale, \
															sizeof(int *));
	i = -1;
	while (++i < p->cfg->mapheight * p->cfg->minimapscale)
		p->buf2D[i] = (int *)calloc_(p->cfg->mapwidth * p->cfg->minimapscale, \
																sizeof(int));
	return (0);
}

void	init(t_param *p)
{
	p->mlx = mlx_init();
	if (!p->mlx)
		exit(1);
	p->win = mlx_new_window(p->mlx, SCREENWIDTH, SCREENHEIGHT, "Raycaster");
	if (!p->win)
		exit(1);
	init_config(p->cfg);
	print_config(p->cfg);
	init_buffer(p);
	init_mlx_img(p);
	make_minimap_img(p);
	load_imgs(p);
	imgs_to_textures(p);
}
