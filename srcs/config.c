/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:30:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:00:12 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_config(t_config* cfg)
{
	cfg->blockscale = SCREENWIDTH / cfg->mapwidth;	// screen Width를 기준으로 블럭의 가로를 정하고 있음. 블럭의 가로에 비례해서 높이를 그려줌.
	cfg->num_rays = SCREENWIDTH;
	cfg->collision_range = cfg->blockscale / 10;
	cfg->minimapscale = cfg->blockscale / 2;
}

void	print_config(t_config* cfg)
{
	printf("\
┌───────────────────────────────────────────────────────────\n\
│                       CONFIGURATIONS\n\
│\n\
│\t%spre-defined%s\n\
│\n\
│	%sscreenWidth%s\t= %d\n\
│	%sscreenHeight%s\t= %d\n\
│	%stexWidth%s\t= %d\n\
│	%stexHeight%s\t= %d\n\
│\n\
│\t%sruntime-configure%s\n\
│\n\
│	%sblockscale%s\t= %d\n\
│	%snum_rays%s\t= %d\n\
│	%scollision_range%s\t= %d\n\
│	%sminimapscale%s\t= %d\n\
│\n\
└───────────────────────────────────────────────────────────\n", \
	CYAN, NC,\
	DCYAN, NC, SCREENWIDTH,\
	DCYAN, NC, SCREENHEIGHT,\
	DCYAN, NC, TEXWIDTH,\
	DCYAN, NC, TEXHEIGHT,\
	PURPLE, NC,\
	DPURPLE, NC, cfg->blockscale,\
	DPURPLE, NC, cfg->num_rays,\
	DPURPLE, NC, cfg->collision_range,\
	DPURPLE, NC, cfg->minimapscale);
}
