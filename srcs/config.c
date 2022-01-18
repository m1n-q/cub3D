/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:30:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 16:50:46 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_config(t_config* C)
{
	C->blockScale = screenWidth / C->mapWidth;	// screen Width를 기준으로 블럭의 가로를 정하고 있음. 블럭의 가로에 비례해서 높이를 그려줌.
	C->NUM_RAYS = screenWidth;
	C->collisionRange = C->blockScale / 10;
	C->minimapScale = C->blockScale / 2;
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
│	%sblockScale%s\t= %d\n\
│	%sNUM_RAYS%s\t= %d\n\
│	%scollisionRange%s\t= %d\n\
│	%sminimapScale%s\t= %d\n\
│\n\
└───────────────────────────────────────────────────────────\n", \
	CYAN, NC,\
	DCYAN, NC, screenWidth,\
	DCYAN, NC, screenHeight,\
	DCYAN, NC, texWidth,\
	DCYAN, NC, texHeight,\
	PURPLE, NC,\
	DPURPLE, NC, C->blockScale,\
	DPURPLE, NC, C->NUM_RAYS,\
	DPURPLE, NC, C->collisionRange,\
	DPURPLE, NC, C->minimapScale);
}
