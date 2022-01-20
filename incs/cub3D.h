/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:40:00 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 19:10:41 by mishin           ###   ########.fr       */
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
# include "get_next_line.h"
# include "map.h"

# define N		NO
# define S		SO
# define W		WE
# define E		EA

# define TOP	0
# define BOTTOM	1
# define FULL	2

# define VERT	0
# define HORZ	1

# define PI		3.141592

typedef void*	(*t_loadfunc)(void*, char*, int*, int*);

void	init(t_param *p);
/* config */
void	init_config(t_config *cfg);
void	print_config(t_config *cfg);

/* DDA algorithm */
t_dda	get_dda_info(t_param *p, double r);
void	run_dda(t_param *p, t_dda *__dda);

/* render */
int		render(t_param *p);
int		raycasting(t_param *p);
void	draw_verline(t_param *p, t_drawinfo draw, int color, int mode);

/* screen buffer */
void	destroy_buffer(t_param *p);//NOTE:unused?
void	clear_buffer(int **buffer, int w, int h);//NOTE:unused?

/* img */
void	load_imgs(t_param *p);
void	clear_img(t_img img, int w, int h);//NOTE:unused?

/* texture */
void	destroy_texture(t_param *p);//NOTE:unused?
void	fill_by_texture(t_param *p, t_dda D, t_drawinfo draw);

/* convert */
int		imgs_to_textures(t_param *p);
void	buffer_to_img(int **buffer, t_img img, int w, int h);

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
void	check_map_leaks(t_param *p, int **map);

int		get_next_line(int fd, char **line);
t_lst	*lst_add_back(t_lst *node, char *content);
void	lst_print(t_lst *head);
void	lst_clear(t_lst **head);
int		lst_get_len(t_lst *node);
t_lst	*lst_get_tail(t_lst *node);

/* utils */
char	*strjoin2_(char *s1, char *s2, char *s3);
char	**ft_split2(char *str, char *ch);
void	err_exit(char *msg, t_param *p);
void	err_exit_(char *msg, t_param *p);
void	print_worldmap(t_param *p);
int		check_val(int c);
int		set_dir(t_param *p, int c);
int		set_pos(t_param *p, int x, int y);
char	*formatstr(char *fstr, char *arg, int tofree);
int		is_empty_line(char *line);

void	*calloc_(size_t count, size_t size);
char	*strdup_(char *s);
char	*strjoin_(const char *s1, const char *s2);
char	*substr_(char const *s, unsigned int start, size_t len);
#endif
