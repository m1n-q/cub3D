/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:46 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 15:14:28 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init(PARAM *P)
{
	P->mlx = mlx_init();
	if (!P->mlx)
		exit(1);
	P->win = mlx_new_window(P->mlx, screenWidth, screenHeight, "Raycaster");
	if (!P->win)
		exit(1);
	init_config(P->cfg);
	init_mlx_image(P);
	load_images(P);
	make_minimap_image(P);
	init_buffer(P);
	init_texture(P);
}
