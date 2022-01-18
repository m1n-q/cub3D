/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:30:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 16:56:33 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_config(t_config* C)
{
	C->blockscale = screenWidth / C->mapwidth;	// screen Width를 기준으로 블럭의 가로를 정하고 있음. 블럭의 가로에 비례해서 높이를 그려줌.
	C->num_rays = screenWidth;
	C->collision_range = C->blockscale / 10;
	C->minimapscale = C->blockscale / 2;
}

void	print_config(t_config* C)
{
	printf("\
┌───────────────────────────────────────────────────────────\n\
│                       t_configURATIONS\n\
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
	DCYAN, NC, screenWidth,\
	DCYAN, NC, screenHeight,\
	DCYAN, NC, texWidth,\
	DCYAN, NC, texHeight,\
	PURPLE, NC,\
	DPURPLE, NC, C->blockscale,\
	DPURPLE, NC, C->num_rays,\
	DPURPLE, NC, C->collision_range,\
	DPURPLE, NC, C->minimapscale);
}
