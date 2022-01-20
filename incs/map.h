/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:32:41 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 17:33:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <fcntl.h>

# define RET_CLEAR	1
# define RET_ERROR	0
# define RET_EOF	-1

# define PLAYER		1
# define WALL_LAND	2
# define SPACE		3

# define NO			0
# define SO			1
# define WE			2
# define EA			3
# define FLOOR		4	// floor rgb
# define CEILI		5	// ceilling rgb
# define UN_DEF		6 	// undefine

# define P_RED		"\x1b[31m"
# define P_RESET	"\x1b[0m"

#endif
