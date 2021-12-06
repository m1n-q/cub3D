#include "cub3D.h"

int	init_texture(PARAM *P)
{
	int	texnum = 5;
	P->texture = (int **)ft_calloc(texnum ,sizeof(int *));
	for (int i = 0; i < texnum; i++)
		P->texture[i] = ft_calloc(texHeight * texWidth, sizeof(int));

	for (int x = 0; x < texWidth; x++)
		for (int y = 0; y < texHeight; y++)
			P->texture[4][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	image_to_texture(P->texture[BORDER], P->wall1);
	image_to_texture(P->texture[1], P->wall2);
	image_to_texture(P->texture[2], P->wall3);
	image_to_texture(P->texture[3], P->wall4);

	return (0);
}

int image_to_texture(int *texture, IMG teximg)
{
	for (int y = 0; y < texHeight; y++)
		for (int x = 0; x < texWidth; x++)
			texture[texWidth * y + x] = teximg.addr[y * teximg.linesize / sizeof(int) + x];

	return (0);
}
