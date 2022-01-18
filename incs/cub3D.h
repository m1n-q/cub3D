/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:40:00 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 15:23:38 by mishin           ###   ########.fr       */
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
# include "get_next_line_bonus.h"
# include "map.h"

# define N		0
# define S		1
# define W		2
# define E		3
# define BORDER	4

# define VERT	0
# define HORZ	1

# define PI		3.141592

typedef void*	(*t_loadfunc)(void*, char*, int*, int*);


void	init(PARAM *P);
/* config */
void	init_config(CONFIG* C);
void	print_config(CONFIG* C);

/* DDA algorithm */
DDA		get_DDA_info(PARAM *P, double r);
void	run_DDA(PARAM *P, DDA *D);

/* render */
int		render(PARAM *P);
int		raycasting(PARAM *P);
//2D
void	draw_dir(PARAM *P);//FIXME
void	draw_perpdir(PARAM *P, VECTOR perp_dir);//FIXME
void	draw_ray(PARAM *P, DDA D);//FIXME
void	draw_2Dmap(PARAM *P);//FIXME
void	draw_2Dplayer(PARAM *P);//FIXME
void	draw_2DCircle(PARAM *P);//FIXME
int		draw_2Dsquare(PARAM *P, int x, int y, IMG img);//FIXME

//3D
void	draw_verLine(int x, int drawStart, int drawEnd, int color, PARAM *P);

/* screen buffer */
int		init_buffer(PARAM *P);//FIXME
void	destroy_buffer(PARAM* P);//FIXME
void	buffer_to_img(int **buffer, IMG img, int w, int h);
void	clear_buffer(int **buffer, int w, int h);
void	clear_img(IMG img, int w, int h);

/* image */
void	load_image(PARAM *P, IMG *I, char *filename);
void	load_images(PARAM *P);
void	make_minimap_image(PARAM *P);//FIXME
void	init_mlx_image(PARAM *P);//FIXME

/* texture */
int		init_texture(PARAM *P);
void	destroy_texture(PARAM *P);
int		image_to_texture(int texture[][texWidth], IMG teximg);
void	fill_by_texture(PARAM *P, DDA D, LINEDRAW draw);

/* event hook */
int		keymap(int keycode, PARAM *param);

/* map_parsing */
void	parse_file(PARAM *P, char *filename);
void	parse_line(PARAM *P, char *line);
void	parse_texture(PARAM *P, int type, char *line);
void	parse_rgb(PARAM *P, int type, char *line);
void	check_worldMap(PARAM *P, CONFIG *C);
void	check_hole(PARAM *P, int y);
void	check_wall(PARAM *P);

int		get_next_line(int fd, char **line);
t_lst	*lst_add_back(t_lst *node, char *content);
void	lst_print(t_lst *head);
void	lst_clear(t_lst **head);
int		lst_get_len(t_lst *node);
t_lst	*lst_get_tail(t_lst *node);

/* utils */
char	**ft_split2(char *str, char *ch);
void	err_exit(char *msg, PARAM *P);
void	print_worldMap(PARAM *P);
int		check_val(int c);
void	wall_leaks_exit(int y, int x, PARAM *P);
int		set_dir(PARAM *P, int c);
int		set_pos(PARAM *P, int x, int y);
char	*formatstr(char *fstr, char *arg, int tofree);

void	*calloc_(size_t count, size_t size);
char	*strdup_(char *s);
char	*strjoin_(const char *s1, const char *s2);
char	*substr_(char const *s, unsigned int start, size_t len);
#endif
