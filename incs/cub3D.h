/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:40:00 by mishin            #+#    #+#             */
/*   Updated: 2022/01/13 19:24:24 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <X11/X.h>
# include <stdbool.h>

# include "mlx.h"
# include "keys.h"
# include "libft.h"
# include "color.h"
# include "config.h"
# include "structs.h"

# define BORDER	0
# define N		1
# define S		2
# define E		3
# define W		4

# define VERT	0
# define HORZ	1

# define PI		3.141592

extern int worldMap[mapWidth][mapHeight];

int		raycasting(PARAM *P);

/* DDA algorithm */
DDA		get_DDA_info(VECTOR pos, VECTOR dir, double r);
void	run_DDA(DDA *D);

/* render */
int		render(PARAM *P);
//2D
void	draw_dir(PARAM *P);
void	draw_perpdir(PARAM *P, VECTOR perp_dir);
void	draw_ray(PARAM *P, DDA D);
void	draw_2Dmap(PARAM *P);
void	draw_2Dplayer(PARAM *P);
void	draw_2DCircle(PARAM *P);

//3D
void	draw_verLine(int x, int drawStart, int drawEnd, int color, PARAM *P);
int		draw_2Dsquare(PARAM *P, int x, int y, IMG img);

/* screen buffer */
int		init_buffer(PARAM *P);
void	destroy_buffer(PARAM* P);
void	buffer_to_img(int **buffer, IMG img, int w, int h);
void	clear_buffer(int **buffer);
void	clear_img(IMG img);

/* image */
int		load_image(PARAM *P);

/* texture */
int		init_texture(PARAM *P);
void	destroy_texture(PARAM *P);
int		image_to_texture(int *texture, IMG teximg);
VECTOR	get_texture_pos(DDA D);
void	fill_by_texture(PARAM *P, DDA D, VECTOR texpos, LINEDRAW draw);

/* event hook */
int		keymap(int keycode, PARAM *param);

/* utils */

#endif
