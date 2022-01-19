/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:43 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 17:17:11 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

// pos_on_wall 한칸에서 어느만큼인지 : hit.x =87, scale =40 -> 3번째 칸에서 7번째 위치
// textureWidth 의 7 / 40 위치를 가져와야 함	(method 2: using floor)
t_vector	get_texture_pos(t_param *p, t_dda __dda)
{
	double		pos_on_wall;
	t_vector	texpos;

	if (__dda.side == HORZ)
		pos_on_wall = (int)__dda.hit.x % p->cfg->blockscale;
	else
		pos_on_wall = (int)__dda.hit.y % p->cfg->blockscale;
	texpos.x = (pos_on_wall / p->cfg->blockscale) * TEXWIDTH;
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

// 전체 그릴 높이 == draw.length
void	fill_by_texture(t_param *p, t_dda __dda, t_drawinfo draw)
{
	int			y;
	int			color;
	int			texidx;
	double		tex_stepy;
	t_vector	texpos;

	texidx = get_texture_idx(__dda);
	texpos = get_texture_pos(p, __dda);
	tex_stepy = (double)TEXHEIGHT / (double)draw.length;
	y = draw.start_y - 1;
	while (++y < draw.end_y)
	{
		if (y < 0 || y >= SCREENHEIGHT)
		{
			texpos.y += tex_stepy;
			continue ;
		}
		texpos.y = fmin(texpos.y, TEXHEIGHT - 1);
		color = p->textures[texidx][(int)texpos.y][(int)texpos.x];
		if (__dda.side == HORZ)
			color = (color >> 1) & 8355711;
		p->buf3D[y][draw.x] = color;					// # method 1
		// set_pixel_color(p->img3D, draw.x, y, color);	// @ method 2
		texpos.y += tex_stepy;
	}
}
