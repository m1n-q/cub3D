/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:37:02 by mishin            #+#    #+#             */
/*   Updated: 2022/01/13 20:51:54 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define mapWidth		25
# define mapHeight		25
# define screenWidth	720
# define screenHeight	720
# define NUM_RAYS		screenWidth	//Resolution
# define BLOCK_SIZE		(screenWidth / mapWidth)
# define SCALE			(screenWidth / NUM_RAYS)
# define collisionRange	5
# define texWidth		256
# define texHeight		256
# define texNum			5


#endif
