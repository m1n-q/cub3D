/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:40:00 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:01:34 by mishin           ###   ########.fr       */
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


void	init(t_param *p);
/* config */
void	init_config(t_config *cfg);
void	print_config(t_config *cfg);

/* DDA algorithm */
t_DDA	get_DDA_info(t_param *p, double r);
void	run_DDA(t_param *p, t_DDA *D);

/* render */
int		render(t_param *p);
int		raycasting(t_param *p);
//2D
void	draw_dir(t_param *p);//FIXME
void	draw_perpdir(t_param *p, t_vector perp_dir);//FIXME
void	draw_ray(t_param *p, t_DDA D);//FIXME
void	draw_2Dmap(t_param *p);//FIXME
void	draw_2Dplayer(t_param *p);//FIXME
void	draw_2DCircle(t_param *p);//FIXME
int		draw_2Dsquare(t_param *p, int x, int y, t_img img);//FIXME

//3D
void	draw_verLine(int x, int drawStart, int drawEnd, int color, t_param *p);

/* screen buffer */
int		init_buffer(t_param *p);//FIXME
void	destroy_buffer(t_param *p);//FIXME
void	buffer_to_img(int **buffer, t_img img, int w, int h);
void	clear_buffer(int **buffer, int w, int h);
void	clear_img(t_img img, int w, int h);

/* image */
void	load_image(t_param *p, t_img *I, char *filename);
void	load_images(t_param *p);
void	make_minimap_image(t_param *p);//FIXME
void	init_mlx_image(t_param *p);//FIXME

/* texture */
int		init_texture(t_param *p);
void	destroy_texture(t_param *p);
int		image_to_texture(int texture[][TEXWIDTH], t_img teximg);
void	fill_by_texture(t_param *p, t_DDA D, t_drawinfo draw);

/* event hook */
int		keymap(int keycode, t_param *param);
int		rotate(int keycode, t_param *p);
int		move(int keycode, t_param *p);
int		quit(int keycode, t_param *p);
int		bye(t_param *p);

/* map_parsing */
void	parse_file(t_param *p, char *filename);
void	parse_line(t_param *p, char *line);
void	parse_texture(t_param *p, int type, char *line);
void	parse_rgb(t_param *p, int type, char *line);
void	check_worldmap(t_param *p, t_config *cfg);
void	check_hole(t_param *p, int y);
void	check_wall(t_param *p);

int		get_next_line(int fd, char **line);
t_lst	*lst_add_back(t_lst *node, char *content);
void	lst_print(t_lst *head);
void	lst_clear(t_lst **head);
int		lst_get_len(t_lst *node);
t_lst	*lst_get_tail(t_lst *node);

/* utils */
char	**ft_split2(char *str, char *ch);
void	err_exit(char *msg, t_param *p);
void	print_worldmap(t_param *p);
int		check_val(int c);
void	wall_leaks_exit(int y, int x, t_param *p);
int		set_dir(t_param *p, int c);
int		set_pos(t_param *p, int x, int y);
char	*formatstr(char *fstr, char *arg, int tofree);

void	*calloc_(size_t count, size_t size);
char	*strdup_(char *s);
char	*strjoin_(const char *s1, const char *s2);
char	*substr_(char const *s, unsigned int start, size_t len);
#endif
