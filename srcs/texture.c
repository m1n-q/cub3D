/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:43 by mishin            #+#    #+#             */
/*   Updated: 2022/01/17 18:28:24 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_texture(PARAM *P)
{
	// int	i;
	// int	j;

	// P->textures = ft_calloc(texNum ,sizeof(int **));
	// i = -1;
	// while (++i < texNum)
	// {
	// 	P->textures[i]= ft_calloc(texHeight, sizeof(int *));
	// 	j = -1;
	// 	while (++j < texHeight)
	// 		P->textures[i][j] = ft_calloc(texWidth, sizeof(int));
	// }
	image_to_texture(P->textures[N], P->wall_N);
	image_to_texture(P->textures[S], P->wall_S);
	image_to_texture(P->textures[W], P->wall_W);
	image_to_texture(P->textures[E], P->wall_E);
	image_to_texture(P->textures[BORDER], P->wall1);
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
	int	j;


	i = -1;
	while (++i < texNum)
	{
		j = -1;
		while (++j < texHeight)
			free(P->textures[i][j]);
		free(P->textures[i]);
	}
	free(P->textures);
}

int	image_to_texture(int texture[][texWidth], IMG teximg)
{
	int	x;
	int	y;

	y = -1;
	while (++y < texHeight)
	{
		x = -1;
		while (++x < texWidth)
			texture[y][x] = teximg.addr[y * teximg.linesize / sizeof(int) + x];
	}
	return (0);
}

VECTOR	get_texture_pos(PARAM *P, DDA D)
{
	double	pos_on_wall;
	VECTOR	texpos;

	// 한칸에서 어느만큼인지 : hit.x =87, scale =40 -> 3번째 칸에서 7번째 위치
	if (D.side == HORZ)
		pos_on_wall = (int)D.hit.x % P->cfg->blockScale;
	else
		pos_on_wall = (int)D.hit.y % P->cfg->blockScale;

	// textureWidth 에서 7 / 40 위치 가져와야 함	(method 2: using floor)
	texpos.x = (pos_on_wall / P->cfg->blockScale) * texWidth;

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

	texidx = get_texture_idx(D);
	texpos = get_texture_pos(P, D);

	// 전체 그릴 높이 == draw.length
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
		color = P->textures[texidx][(int)texpos.y][(int)texpos.x];
		if (D.side == HORZ)
			color = (color >> 1) & 8355711;
		P->buf3D[y][draw.x]	= color;
		texpos.y += tex_stepY;
	}
}
