/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:37:02 by mishin            #+#    #+#             */
/*   Updated: 2022/01/11 11:38:05 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define mapWidth		25
# define mapHeight		25
# define screenWidth	500
# define screenHeight	500
# define BLOCK_SIZE		(screenWidth / mapWidth)
# define NUM_RAYS		screenWidth
# define SCALE			(screenWidth / NUM_RAYS)

# define texWidth		256
# define texHeight		256

#endif
