/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:30:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 22:55:24 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_config(CONFIG* C)
{
	// C->mapWidth = 0;
	// C->mapHeight = 0;
	C->screenWidth = 1080;
	C->screenHeight = 720;
	C->blockScale = C->screenWidth / C->mapWidth;	// screen Width를 기준으로 블럭의 가로를 정하고 있음. 블럭의 가로에 비례해서 높이를 그려줌.
	C->NUM_RAYS = C->screenWidth;
	C->SCALE =	C->screenWidth / C->NUM_RAYS;
	C->collisionRange = C->blockScale / 10;
	C->minimapScale = C->blockScale / 10;
}
