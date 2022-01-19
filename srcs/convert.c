/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:10:13 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 17:03:59 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	img_to_texture(int texture[][TEXWIDTH], t_img teximg)
{
	int	x;
	int	y;

	y = -1;
	while (++y < TEXHEIGHT)
	{
		x = -1;
		while (++x < TEXWIDTH)
			texture[y][x] = teximg.addr[y * teximg.linesize / sizeof(int) + x];
	}
	return (0);
}

int	imgs_to_textures(t_param *p)
{
	img_to_texture(p->textures[N], p->wall_n);
	img_to_texture(p->textures[S], p->wall_s);
	img_to_texture(p->textures[W], p->wall_w);
	img_to_texture(p->textures[E], p->wall_e);
	mlx_destroy_image(p->mlx, p->wall_n.img);
	mlx_destroy_image(p->mlx, p->wall_s.img);
	mlx_destroy_image(p->mlx, p->wall_w.img);
	mlx_destroy_image(p->mlx, p->wall_e.img);
	return (0);
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

void	set_pixel_color(t_img i, int x, int y, int color)
{
	i.addr[y * i.linesize / sizeof(int) + x] = color;
}
