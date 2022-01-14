/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:43 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 17:08:17 by mishin           ###   ########.fr       */
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
	image_to_texture(P->texture[BORDER], P->wall1);
	image_to_texture(P->texture[1], P->wall2);
	image_to_texture(P->texture[2], P->wall3);
	image_to_texture(P->texture[3], P->wall4);
	image_to_texture(P->texture[4], P->wall5);
	mlx_destroy_image(P->mlx, P->wall1.img);
	mlx_destroy_image(P->mlx, P->wall2.img);
	mlx_destroy_image(P->mlx, P->wall3.img);
	mlx_destroy_image(P->mlx, P->wall4.img);
	mlx_destroy_image(P->mlx, P->wall5.img);
	return (0);
}

void	destroy_texture(PARAM *P)
{
	for (int i = 0; i < texNum; i++)
		free(P->texture[i]);
	free(P->texture);
}

int image_to_texture(int *texture, IMG teximg)
{
	for (int y = 0; y < texHeight; y++)
		for (int x = 0; x < texWidth; x++)
			texture[texWidth * y + x] = teximg.addr[y * teximg.linesize / sizeof(int) + x];
	return (0);
}

VECTOR	get_texture_pos(DDA D)
{
	double wall_hit;
	VECTOR texpos;

	if (D.side == 0)	wall_hit = D.hit.y / blockScale;
	else				wall_hit = D.hit.x / blockScale;

	// 1칸에서 어느만큼인지 * texWidth
	texpos.x = ((wall_hit - floor(wall_hit)) * (double)texWidth);

	// 좌우반전
	if (D.side == HORZ && D.raydir.y > 0)	texpos.x = texWidth - texpos.x - 1;
	if (D.side == VERT && D.raydir.x < 0)	texpos.x = texWidth - texpos.x - 1;
	texpos.y = 0.0;

	return (texpos);
}

void	fill_by_texture(PARAM *P, DDA D, VECTOR texpos, LINEDRAW draw)
{
	int		color;
	int		texnum;
	double	tex_stepY;

	//전체 그릴 높이 == draw.length
	//How much to increase the texture coordinate per screen pixel
	tex_stepY = (double)texHeight / (double)draw.length;	// drawStart 일때 tespos.y == 0, drawEnd 일때 tespos.y == 0 되도록

	texnum = P->worldMap[(int)(D.hit.y / blockScale)][(int)(D.hit.x / blockScale)] - 1;
	for (int y = draw.start_y; y < draw.end_y; y++)
	{
		if (y < 0 || y >= screenHeight)
		{
			texpos.y += tex_stepY;
			continue ;
		}
		texpos.y	= fmin(texpos.y, texHeight - 1);

		color		= P->texture[texnum][(int)texpos.y * texHeight + (int)texpos.x];

		if (D.side == HORZ)
			color = (color >> 1) & 8355711;	// make color darker for horizontal sides


		P->buf3D[y][draw.x]	= color;

		texpos.y += tex_stepY;
	}
}
