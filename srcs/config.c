/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:30:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/17 18:57:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_config(CONFIG* C)
{
	C->blockScale = screenWidth / C->mapWidth;	// screen Width를 기준으로 블럭의 가로를 정하고 있음. 블럭의 가로에 비례해서 높이를 그려줌.
	C->NUM_RAYS = screenWidth;
	C->collisionRange = C->blockScale / 10;
	C->minimapScale = C->blockScale / 2;

	printf("\
	screenWidth = %d\n \
	screenHeight = %d\n \
	C->blockScale = %d\n \
	C->NUM_RAYS = %d\n \
	C->collisionRange = %d\n \
	C->minimapScale = %d\n",
	screenWidth,
	screenHeight,
	C->blockScale,
	C->NUM_RAYS,
	C->collisionRange,
	C->minimapScale
	);
}
