/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:43 by mishin            #+#    #+#             */
/*   Updated: 2022/01/17 16:12:49 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: texture		=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)
int	init_texture(PARAM *P)
{
	int	i;

	P->texture = (int **)ft_calloc(texNum ,sizeof(int *));
	i = -1;
	while (++i < texNum)
		P->texture[i] = ft_calloc(texHeight * texWidth, sizeof(int));
	image_to_texture(P->texture[N], P->wall_N);
	image_to_texture(P->texture[S], P->wall_S);
	image_to_texture(P->texture[W], P->wall_W);
	image_to_texture(P->texture[E], P->wall_E);
	image_to_texture(P->texture[BORDER], P->wall1);
	mlx_destroy_image(P->mlx, P->wall1.img);
	mlx_destroy_image(P->mlx, P->wall2.img);
	mlx_destroy_image(P->mlx, P->wall3.img);
	mlx_destroy_image(P->mlx, P->wall4.img);
	mlx_destroy_image(P->mlx, P->wall5.img);
	mlx_destroy_image(P->mlx, P->wall_N.img);
	mlx_destroy_image(P->mlx, P->wall_S.img);
	mlx_destroy_image(P->mlx, P->wall_W.img);
	mlx_destroy_image(P->mlx, P->wall_E.img);
	return (0);
}

void	destroy_texture(PARAM *P)
{
	int	i;

	i = -1;
	while (++i < texNum)
		free(P->texture[i]);
	free(P->texture);
}

int	image_to_texture(int *texture, IMG teximg)
{
	int	x;
	int	y;

	y = -1;
	while (++y < texHeight)
	{
		x = -1;
		while (++x < texWidth)
			texture[texWidth * y + x] = \
							teximg.addr[y * teximg.linesize / sizeof(int) + x];
	}
	return (0);
}

VECTOR	get_texture_pos(PARAM *P, DDA D)
{
	double	wall_hit;
	VECTOR	texpos;

	if (D.side == 0)
		wall_hit = D.hit.y / P->cfg->blockScale;
	else
		wall_hit = D.hit.x / P->cfg->blockScale;
	// 1칸에서 어느만큼인지 * P->cfg->texWidth
	texpos.x = ((wall_hit - floor(wall_hit)) * (double)texWidth);
	// 좌우반전
	if (D.side == HORZ && D.raydir.y > 0)
		texpos.x = texWidth - texpos.x - 1;
	if (D.side == VERT && D.raydir.x < 0)
		texpos.x = texWidth - texpos.x - 1;
	texpos.y = 0.0;
	return (texpos);
}

int	get_texture_idx(DDA D)
{
	if (D.side == HORZ)
	{
		if (D.raydir.y >= 0)
			return (N);
		else
			return (S);
	}
	else
	{
		if (D.raydir.x >= 0)
			return (W);
		else
			return (E);
	}
}

void	fill_by_texture(PARAM *P, DDA D, LINEDRAW draw)
{
	int		y;
	int		color;
	int		texidx;
	double	tex_stepY;
	VECTOR	texpos;

	texpos = get_texture_pos(P, D);
	texidx = get_texture_idx(D);
	// 전체 그릴 높이 == draw.length
	// How much to increase the texture coordinate per screen pixel
	// drawStart 일때 tespos.y == 0, drawEnd 일때 tespos.y == 0 되도록
	tex_stepY = (double)texHeight / (double)draw.length;

	y = draw.start_y - 1;
	while (++y < draw.end_y)
	{
		if (y < 0 || y >= P->cfg->screenHeight)
		{
			texpos.y += tex_stepY;
			continue ;
		}
		texpos.y = fmin(texpos.y, texHeight - 1);
		color = P->texture[texidx][(int)texpos.y * texHeight + (int)texpos.x];
		if (D.side == HORZ)
			color = (color >> 1) & 8355711;
		P->buf3D[y][draw.x]	= color;
		texpos.y += tex_stepY;
	}
}
