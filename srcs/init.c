/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:46 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 17:54:41 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	init_mlx_image(p);
	load_images(p);
	make_minimap_image(p);
	init_buffer(p);
	init_texture(p);
}
