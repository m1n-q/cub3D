/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:43 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:13:27 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_texture(t_param *p)
{
	image_to_texture(p->textures[N], p->wall_n);
	image_to_texture(p->textures[S], p->wall_s);
	image_to_texture(p->textures[W], p->wall_w);
	image_to_texture(p->textures[E], p->wall_e);
	mlx_destroy_image(p->mlx, p->wall_n.img);
	mlx_destroy_image(p->mlx, p->wall_s.img);
	mlx_destroy_image(p->mlx, p->wall_w.img);
	mlx_destroy_image(p->mlx, p->wall_e.img);
	return (0);
}

void	destroy_texture(t_param *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TEXNUM)
	{
		j = -1;
		while (++j < TEXHEIGHT)
			free(p->textures[i][j]);
		free(p->textures[i]);
	}
	free(p->textures);
}

int	image_to_texture(int texture[][TEXWIDTH], t_img teximg)
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

t_vector	get_texture_pos(t_param *p, t_dda __dda)
{
	double	pos_on_wall;
	t_vector	texpos;

	// 한칸에서 어느만큼인지 : hit.x =87, scale =40 -> 3번째 칸에서 7번째 위치
	if (__dda.side == HORZ)
		pos_on_wall = (int)__dda.hit.x % p->cfg->blockscale;
	else
		pos_on_wall = (int)__dda.hit.y % p->cfg->blockscale;

	// textureWidth 에서 7 / 40 위치 가져와야 함	(method 2: using floor)
	texpos.x = (pos_on_wall / p->cfg->blockscale) * TEXWIDTH;

	// 좌우반전
	if (__dda.side == HORZ && __dda.raydir.y > 0)
		texpos.x = TEXWIDTH - texpos.x - 1;
	if (__dda.side == VERT && __dda.raydir.x < 0)
		texpos.x = TEXWIDTH - texpos.x - 1;
	texpos.y = 0.0;
	return (texpos);
}

int	get_texture_idx(t_dda __dda)
{
	if (__dda.side == HORZ)
	{
		if (__dda.raydir.y >= 0)
			return (N);
		else
			return (S);
	}
	else
	{
		if (__dda.raydir.x >= 0)
			return (W);
		else
			return (E);
	}
}

void	fill_by_texture(t_param *p, t_dda __dda, t_drawinfo draw)
{
	int			y;
	int			color;
	int			texidx;
	double		tex_stepY;
	t_vector	texpos;

	texidx = get_texture_idx(__dda);
	texpos = get_texture_pos(p, __dda);

	// 전체 그릴 높이 == draw.length
	tex_stepY = (double)TEXHEIGHT / (double)draw.length;
	y = draw.start_y - 1;
	while (++y < draw.end_y)
	{
		if (y < 0 || y >= SCREENHEIGHT)
		{
			texpos.y += tex_stepY;
			continue ;
		}
		texpos.y = fmin(texpos.y, TEXHEIGHT - 1);
		color = p->textures[texidx][(int)texpos.y][(int)texpos.x];
		if (__dda.side == HORZ)
			color = (color >> 1) & 8355711;
		p->buf3D[y][draw.x]	= color;
		texpos.y += tex_stepY;
	}
}
